#include "../inc/minishell.h"

char	*ft_add(char **newenvp, char *ag)
{
	char	*cmd1;
	char	**str;
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	str = get_path(newenvp);
	args = ft_split(ag, ' ');
	if (!*str)
		return (NULL);
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		cmd1 = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (access(cmd1, X_OK) == 0)
			return (free(str), free(args), cmd1);
		free(cmd1);
		i++;
	}
	return (free(str),free(args), NULL);
}

char	**get_path(char **newenv)
{
	int		i;
	char	*str;
	char	**newstr;

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

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}

void	new_string(char *str, t_mini *mini)
{
	int	i;
	int	j;

	mini->new_str = ft_calloc((ft_strlen(str) - 1), sizeof(char));
	i = 0;
	j = 0;
	if(check_args(str) == 1)
	{
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
				mini->new_str[j++] = str[i];
			i++;
		}
		mini->new_str[j] = '\0';
	}
	else
		mini->new_str = ft_strdup(str);
}

/*
* Function to copy the envp
*/
char	**get_newenvp(char **envp)
{
	char	**newenvp;
	int		i;
	int		j;

	i = 0;
	while(envp[i])
		i++;
	newenvp = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while(envp[i])
	{	
		j = 0;
		while(envp[i][j])
			j++;
		newenvp[i] = (char *)malloc((j + 1) * sizeof(char));
		j = 0;
		while(envp[i][j])
		{
			newenvp[i][j] = envp[i][j];
			j++;
		}
		newenvp[i][j] = '\0';
		i++;
	}
	return (newenvp[i] = NULL, newenvp);
}