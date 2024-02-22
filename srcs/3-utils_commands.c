#include "../inc/minishell.h"

char *ft_add(t_mini *mini, char *ag)
{
	char *cmd1;
	char **str;
	char *tmp;
	int i;


	str = get_path(mini->newenvp);
	if (!*str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		cmd1 = ft_strjoin(tmp, ag);
		free(tmp);
		if (access(cmd1, X_OK) == 0)
			return (free(str), cmd1);
		free(cmd1);
		i++;
	}
	return (free(str), NULL);
}
void put_cmd(t_mini *mini, char *str)
{
	char **args;
	int i;
	int j;

	args = ft_split(str, ' ');
	j = 0;
	while (args[j])
		j++;
	mini->cmd1 = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (args[i])
	{
		mini->cmd = ft_add(mini, args[i]);
		if (!mini->cmd)
			mini->cmd1[i] = mini->cmd;
		else
			mini->cmd1[i] = ft_strdup(mini->cmd);
		free(mini->cmd);
		i++;
	}
	mini->cmd1[i] = NULL;
}

char **get_path(char **newenv)
{
	int i;
	char *str;
	char **newstr;

	i = 0;
	newstr = NULL;
	if (!newenv[i])
		return (NULL);
	while (newenv[i])
	{
		if (!ft_strncmp(newenv[i], "PATH=", 5))
			str = ft_substr(newenv[i], 5, ft_strlen(newenv[i]));
		i++;
	}
	if (str)
		newstr = ft_split(str, ':');
	free(str);
	return (newstr);
}


/*
Faz uma copia da str devolvida pela readline
*/
// void new_string(char *str, t_mini *mini)
// {
// 	int i;
// 	int j;

// 	mini->new_str = ft_calloc((ft_strlen(str) + 1), sizeof(char));
// 	i = 0;
// 	j = 0;
// 	if (check_args(str) == 1)
// 	{
// 		while (str[i])
// 		{
// 			if (str[i] != '\'' && str[i] != '\"')
// 				mini->new_str[j++] = str[i];
// 			i++;
// 		}
// 		mini->new_str[j] = '\0';
// 	}
// 	else
// 		mini->new_str = ft_strdup(str);
// }

/*
 * Function to copy the envp
 */
char **get_newenvp(char **envp)
{
	char **newenvp;
	int i;
	int j;

	i = 0;
	while (envp[i])
		i++;
	newenvp = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
			j++;
		newenvp[i] = (char *)malloc((j + 1) * sizeof(char));
		j = 0;
		while (envp[i][j])
		{
			newenvp[i][j] = envp[i][j];
			j++;
		}
		newenvp[i][j] = '\0';
		i++;
	}
	return (newenvp[i] = NULL, newenvp);
}
