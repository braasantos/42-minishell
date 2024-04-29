/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:04 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:29:05 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_pipes(t_mini *mini)
{
	int	i;
	int	n_pipes;

	n_pipes = count_pipes(mini->args);
	mini->pipes_fd = malloc(sizeof(int) * (n_pipes * 2));
	i = 0;
	while (i < n_pipes)
	{
		if (pipe(mini->pipes_fd + (2 * i)) < 0)
		{
			ft_fprintf(2, "Minishell: Error while creating pipes\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	handle_pipes(t_mini *mini, int i, int flag)
{
	if (flag == 1)
	{
		if (i == 0)
			dup2(mini->pipes_fd[1], STDOUT_FILENO);
		else if (i == count_pipes(mini->args))
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
	n_pipes = count_pipes(mini->args);
	while (i < n_pipes * 2)
	{
		close(mini->pipes_fd[i]);
		i++;
	}
	free(mini->pipes_fd);
}
