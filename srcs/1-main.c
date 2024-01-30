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
// char	**withoutquotes(char *str)
// {
// 	int		i;
// 	char	**newstr;

// 	i = 0;
// 	newstr = (char *)malloc((ft_strlen(str) - 1) * sizeof(char));
// 	while(str[i])
// 	{
// 		if(str[i] == '"')
// 			i++;
// 		else
// 		newstr[i] = str[i];
// 		i++;
// 	}
// 	newstr[i] = '\0';
// 	return (newstr);
// }
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
void	get_commands(char *args)
{
	char *home_dir;
	home_dir = getenv("HOME");
	if (args == NULL)
		chdir(home_dir);
	else
		if(chdir(args))
			printf("error with cd\n");
}

void	get_wd( t_mini *mini, char *str)
{
	pid_t	fo;
	char	**args;

	args = ft_split(str, ' ');
	if(ft_strcmp(args[0], "cd") == 0)
		get_commands(args[1]);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
        free(args);
        exit(0);
	}
	else
	{
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
}

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
		str = readline("\033[0;34mminishell \033[0m");
		if (str[0])
		{
			add_history(str);
			mini.cmd = ft_add(mini.newenvp, str);
			get_wd(&mini, str);
		}
		free(str);
	}
}
