/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:54:36 by pabernar          #+#    #+#             */
/*   Updated: 2024/04/16 18:26:34 by braasantos       ###   ########.fr       */
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

void	free_eof(t_mini *mini)
{
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
}

void	signals(int sig, t_mini *mini)
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
		free_eof(mini);
		exit(0);
	}
}
