#include "../inc/minishell.h"

void builtins(t_mini *mini)
{
	if (mini->args == NULL)
		return;
	else if (!ft_strcmp(mini->args[0], "exit"))
		ft_exit(mini);
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
