#include "../inc/minishell.h"

void ft_exit(t_mini *mini)
{
	free(mini->args);
	free(mini->new_str);
	free(mini->newenvp);
	exit(1);
}

void parsing(t_mini *mini)
{
	mini->args = ft_split(mini->new_str, ' ');
	put_cmd(mini);

	if (check_commands(mini) == 1)
		return ;
	if (builtins(mini) == 1)
		return ;
	mini->newpro = fork();
	if (mini->newpro == 0)
	{
		if (!mini->cmd1[0])
			print(COMMAND_NOT_FOUND, mini->args[0]);
		else if (execve(mini->cmd1[0], mini->args, mini->newenvp) == -1)
			ft_exit(mini);
	}
	else
		waitpid(-1, NULL, 0);
}
