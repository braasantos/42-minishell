/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:32:14 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:32:17 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_on_child(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (signal == SIGPIPE)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_handle_eof(t_mini *mini)
{
	ft_printf("exit\n");
	ft_free_arr(mini->envp);
	free(mini->str);
	exit(0);
}

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
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
