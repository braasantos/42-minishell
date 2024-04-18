#include "../../inc/minishell.h"

void sig_quit_handler(int sig)
{
	ft_fprintf(2, "quit (core dumped)\n");
	(void)sig;
	g_signal = 131;
}

void	sigint_on_child(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, back_to_prompt);
	signal(SIGQUIT, SIG_IGN);
}