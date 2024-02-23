#include "../../inc/minishell.h"

void ft_exit(t_mini *mini)
{
	ft_free_arr(mini->args);
	ft_free_arr(mini->cmd1);
	free(mini->cmd);
	free(mini->new_str);
	ft_free_arr(mini->newenvp);
	exit(1);
}

void parsing(t_mini *mini, char *str)
{
	mini->new_str = pad_central(str);
	mini->args = ft_split(mini->new_str, ' ');
	if (mini->args[0] == NULL)
		return ;
	put_cmd(mini, str);
	if (!ft_check_open_quotes(str))
		return;
	if (!redirect_basic_check(str))
		ft_printf("invalid redirect\n");
	if (!pipe_check(str))
		ft_printf("Unexpected near '|'\n");
	if (builtins(mini) == 1)
		return;
	execute(mini);
}

void create_child(t_mini *mini, char *s)
{
	pid_t newpro;

	update_path(mini, s);
	newpro = fork();
	if (newpro == 0)
	{
		if (execve(mini->path_to_cmd, mini->exec_args, mini->newenvp) == -1)
			ft_exit(mini);
	}
	else
		waitpid(newpro, NULL, 0);
}
