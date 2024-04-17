/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:27 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 18:29:13 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_pipes(t_mini *mini)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}
int	pipe_creation(t_mini *mini)
{
	int	i;
	int	n_pipes;

	n_pipes = count_pipes(mini);
	mini->pipes_fd = malloc(sizeof(int) * (n_pipes * 2));
	i = 0;
	while (i < n_pipes)
	{
		if (pipe(mini->pipes_fd + (2 * i)) < 0)
		{
			ft_putstr_fd("Error while creating pipes", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	through_pipes(t_mini *mini, int i, int flag)
{
	if (flag == 1)
	{
		if (i == 0)
			dup2(mini->pipes_fd[1], STDOUT_FILENO);
		else if (i == count_pipes(mini))
			dup2(mini->pipes_fd[2 * i - 2], STDIN_FILENO);
		else
		{
			dup2(mini->pipes_fd[2 * i - 2], STDIN_FILENO);
			dup2(mini->pipes_fd[2 * i + 1], STDOUT_FILENO);
		}
		close_pipes(mini);
	}
}

void	close_pipes(t_mini *mini)
{
	int	i;
	int	n_pipes;

	i = 0;
	n_pipes = count_pipes(mini);
	while (i < n_pipes * 2)
	{
		close(mini->pipes_fd[i]);
		i++;
	}
	free(mini->pipes_fd);
}
