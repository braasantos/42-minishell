#include "../../inc/minishell.h"

void	sigint_on_child(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}