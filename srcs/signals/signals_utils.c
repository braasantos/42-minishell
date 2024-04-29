/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:32:20 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:32:21 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_handle_doc(int sig)
{
	g_signal = sig;
	ft_putchar_fd('\n', 1);
	exit_heredoc(return_mini(NULL));
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
