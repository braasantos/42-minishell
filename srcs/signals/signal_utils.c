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
	if (signal == SIGPIPE)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handler_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 2);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: (core dumped)\n", 2);
	g_signal = 128 + signum;
}

void	sigpipe_handler(int signum)
{
	(void)signum;
    printf("Child process received SIGPIPE signal\n");
    exit(EXIT_FAILURE); // Exit with failure status
}
void	signals_child(void)
{
	struct sigaction sa;

    sa.sa_handler = sigpipe_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGPIPE, &sa, NULL);
	signal(SIGINT, handler_child);
	signal(SIGQUIT, handler_child);
}

