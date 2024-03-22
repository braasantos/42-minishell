/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:27 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/21 13:23:46 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	through_pipes(t_mini *mini, int i)
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
