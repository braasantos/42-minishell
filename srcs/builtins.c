#include "../inc/minishell.h"

int str_len(char **str)
{
    int i = 0;

    while (str[i] != NULL)
        i++;
    return (i);
}

int check_red(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], ">") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], "<") == 0 )
			return (2);
		i++;
	}
	return (0);
}

int check_commands(t_mini *mini)
{
	if (exec_pipes(mini) == 1)
		return (1);
	if (redirect_cmd(mini) == 1)
		return (1);
	return (0);
}

int builtins(t_mini *mini)
{
	if (mini->args == NULL)
		return (1);
	if ((!ft_strcmp(mini->args[0], "cd")) || (!ft_strcmp(mini->args[0], "~")))
	{
		get_cd(mini->args[1], mini);
		return (1);
	}
	else if (!ft_strcmp(mini->args[0], "exit"))
		ft_exit(mini);
	return (0);	
}

void get_cd(char *args, t_mini *mini)
{
	char *home_dir;

	home_dir = getenv("HOME");
	if (args == NULL || ft_strcmp(args, "~") == 0)
		chdir(home_dir);
	else if (args[0] == '$')
		chdir(getenv(args + 1));
	else if (chdir(args))
	{
		printf("error with cd\n");
		ft_exit(mini);
	}
}
