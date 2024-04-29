/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:27:19 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:27:20 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	red_out(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
			return (1);
		if (!ft_strcmp(mini->args[i], ">>"))
			return (1);
		i++;
	}
	return (0);
}

int	red_in(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], "<"))
			return (1);
		i++;
	}
	return (0);
}

void	handler_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 2);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: (core dumped)\n", 2);
	g_signal = 128 + signum;
}

void	signals_child(void)
{
	signal(SIGINT, handler_child);
	signal(SIGQUIT, handler_child);
}

int	check_pos_str(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">"))
			return (i);
		if (!ft_strcmp(s[i], "<"))
			return (i);
		if (!ft_strcmp(s[i], ">>"))
			return (i);
		if (!ft_strcmp(s[i], "<<"))
			return (i);
		i++;
	}
	return (0);
}
