/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:54:36 by pabernar          #+#    #+#             */
/*   Updated: 2024/04/19 15:39:06 by bjorge-m         ###   ########.fr       */
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

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handle_sigint_ign(int sig)
{
	if (sig == SIGINT)
		g_signal = sig;
}

void	ft_handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
		g_signal = sig;
}

void	ft_handle_doc(int sig)
{
	g_signal = sig;
	ft_putchar_fd('\n', 1);
	exit(-1);
}

void	ft_init_signals(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_ignore_signals(void)
{
	signal(SIGINT, ft_handle_sigint_ign);
	signal(SIGQUIT, ft_handle_sigquit);
}
void	ft_restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
void	ft_doc_signals(void)
{
	signal(SIGINT, ft_handle_doc);
	signal(SIGQUIT, SIG_IGN);
}