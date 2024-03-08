#include "../../inc/minishell.h"

char *ft_add(t_mini *mini, char *ag)
{
	char *cmd1;
	char **str;
	char *tmp;
	int i;

	tmp = NULL;
	str = get_path(mini->newenvp);
	if (access(ag, X_OK) == 0)
		return (ft_free_arr(str), ft_strdup(ag));
	if (!*str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		cmd1 = ft_strjoin(tmp, ag);
		free(tmp);
		if (access(cmd1, X_OK) == 0)
			return (ft_free_arr(str), cmd1);
		free(cmd1);
		i++;
	}
	return (ft_free_arr(str), NULL);
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
 * Function to copy the envp
 */
char **get_newenvp(char **envp)
{
	char **newenvp;
	int i;
	int j;

	i = str_len(envp);
	newenvp = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		j = ft_strlen(envp[i]);
		newenvp[i] = (char *)malloc((j + 1) * sizeof(char));
		if (newenvp[i] == NULL)
			return (ft_free_arr(newenvp), NULL);
		j = 0;
		while (envp[i][j])
		{
			newenvp[i][j] = envp[i][j];
			j++;
		}
		newenvp[i][j] = '\0';
		i++;
	}
	newenvp[i] = NULL;
	return (newenvp);
}

void while_loop(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		ft_printf("%s\n", s[i]);
		i++;
	}
}
bool is_a_append_here(char *s)
{
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
			return (true);
	return (false);
}