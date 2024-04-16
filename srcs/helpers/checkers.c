/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:09:37 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 18:38:40 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_red(t_mini *mini)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "<") == 0
			|| ft_strcmp(mini->args[i], ">") == 0
			|| !ft_strcmp(mini->args[i], ">>"))
			count++;
		i++;
	}
	return (count);
}

int	count_files(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_a_file(s[i]))
			count++;
		i++;
	}
	return (count);
}

int	bingo(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_grep(t_mini *mini, int i)
{
	i++;
	i++;
	if (is_a_red(mini->args[i]))
		i++;
	while (mini->args[i])
	{
		if (!is_a_file(mini->args[i]))
		{
			ft_putendl_fd(" No such file or directory", 2);
			g_signal = 2;
			return (1);
		}
		i++;
	}
	return (0);
}
