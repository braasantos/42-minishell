/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:54:36 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/23 19:01:04 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	ft_handle_eof(void)
{
	rl_replace_line("exit", 0);
	rl_redisplay();
	printf("\n");
	exit(0);
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
	{
		g_signal = sig;
		printf("Quit (core dumped)");
	}
}