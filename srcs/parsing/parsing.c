#include "../../inc/minishell.h"

void ft_exit(t_mini *mini)
{
	ft_free_arr(mini->args);
	free(mini->new_str);
	ft_free_arr(mini->newenvp);
	exit(1);
}

void parsing(t_mini *mini, char *str)
{
	if (!ft_check_open_quotes(str))
		return;
	if (check_inutils(mini))
		return ;
	// if (!redirect_basic_check(str))
	//  	ft_printf("invalid redirect\n");
	if (!pipe_check(str))
		ft_printf("Minishell: syntax error near unexpected token ``|'\n");
	execute(mini);
}
void sigint_on_child(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void get_exit_status(t_mini *mini)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (i < count_pipes(mini) + 1)
	{
		signal(SIGINT, &sigint_on_child);
		waitpid(mini->newpro[i], &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
		i++;
	}
}