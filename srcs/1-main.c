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

int	check_args(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			j++;
		i++;
	}
	if (j >= 1)
		return (1);
	else
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
void get_wd(t_mini *mini, char *str)
{
	new_string(str, mini);
    mini->args = ft_split(mini->new_str, ' ');
	if (mini->args[0]== NULL)
		return ;
    if (ft_strchr(mini->args[0], '/'))
        mini->cmd = ft_strdup(mini->args[0]);
    else
        mini->cmd = ft_add(mini->newenvp, mini->new_str);
    if (ft_strcmp(mini->args[0], "cd") == 0)
        get_commands(mini->args[1]);
	else if (ft_strcmp(mini->args[0], "exit") == 0) 
		  exit(0);
	else
	{
        mini->newpro = fork();
        if (mini->newpro == 0)
		{
            if (!mini->cmd)
                print(COMMAND_NOT_FOUND, mini->args[0]);
            if (execve(mini->cmd, mini->args, mini->newenvp) == -1)
                exit(EXIT_FAILURE);
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
int	main(int ac, char **av)
{
	t_mini	mini;
	char	*str;
	extern char **environ;

	mini.newenvp = get_newenvp(environ);
	if (ac >= 2 && av)
		return (ft_printf("pls do not use arguments :(\n"));
	while (1)
	{
		str = readline("\033[0;34mminishell \033[0m");
		if (str[0])
		{
			add_history(str);
			get_wd(&mini, str);
		}
		free(str);
	}
}
