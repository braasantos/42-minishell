#include "../inc/minishell.h"

void	print(t_op op, char *ag)
{
	if (op == COMMAND_NOT_FOUND)
		printf("%s: command not found\n", ag);
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

void	get_wd( t_mini *mini, char *str)
{
	pid_t	fo;
	char	**args;

	args = ft_split(str, ' ');
	fo = fork();
	if (fo == 0)
	{
		if (!mini->cmd)
			print(COMMAND_NOT_FOUND, args[0]);
		if (execve(mini->cmd, args, mini->newenvp) == -1)
			exit(2);
	}
	else
		waitpid(-1, NULL, 0);
}

char	**get_newenvp(char **envp)
{
	char	**newenvp;
	auto int	i = 0;
	int		j;

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
	newenvp[i] = NULL;
	return (newenvp);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	char	*str;
	mini.newenvp = get_newenvp(envp);
	(void)av;
	if (ac >= 2)
		return (ft_printf("pls do not use arguments :(\n"));
	while (1)
	{
		str = readline("minishell ");
		add_history(str);
		mini.cmd = ft_add(mini.newenvp, str);
		get_wd(&mini, str);
		free(str);
	}
}
