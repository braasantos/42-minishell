/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:54:36 by pabernar          #+#    #+#             */
/*   Updated: 2024/03/12 15:02:04 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_signals(int sig, void *mini)
{
	static t_mini	*static_mini;

	if (!static_mini && mini)
		static_mini = (t_mini *)mini;
	if (static_mini && static_mini->interact)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			printf("\b\b  \b\b");
			rl_redisplay();
		}
	}
	if (!(static_mini->interact))
		if (sig == SIGINT)
			write(1, "\n", 1);
	if (sig == SIGINT)
		g_signal = 130;
}

static void	signals_handler(int sig)
{
	exec_signals(sig, 0);
}

void	signals_start(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = &signals_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}