/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:54:36 by pabernar          #+#    #+#             */
/*   Updated: 2024/03/22 15:09:26 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	backslash(int sig)
{
	g_signal = 131;
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_signal = 142;
	write(1, "\n", 1);
	(void)sig;
}

void	back_to_prompt(int sig)
{
	g_signal = 142;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, back_to_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, backslash);
	}
	if (sig == 3)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	twenty_six_lines(t_mini *mini)
{
	close_pipes(mini);
	get_exit_status(mini);
}
