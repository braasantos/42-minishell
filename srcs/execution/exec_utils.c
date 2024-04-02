/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:09:09 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/02 17:40:51 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void handle_append2(t_mini *mini, int i)
{
	int file;

	if (mini->args[i + 1])
	{
		file = open(mini->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (!file)
		{
			ft_putstr_fd("Minishell: no file specified in redirect '>>'.\n", 2);
			return;
		}
		close(file);
	}
	else
		return;
}

int check_here(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "<<"))
	{
		handle_heredoc(mini, 0);
		return (1);
	}
	if (!ft_strcmp(mini->args[0], ">>"))
	{
		handle_append2(mini, 0);
		return (1);
	}
	return (0);
}

void ft_exit_builtin(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
	{
		mini->exit_flag = 1;
		unlink(".heredoc");
		free_struct_2(mini);
	}
}

void print_cmd(t_mini *mini, int i)
{
	if (is_a_cmd(mini->args[i], mini) == false && is_a_builtin(mini, i) == false)
		print(COMMAND_NOT_FOUND, mini->args[i]);
}

void handle_execve(t_mini *mini, int i)
{
	if (!is_a_cmd(mini->args[i], mini))
	{
		print_cmd(mini, i);
		exit_fork(mini);
	}
	if (execve(mini->path_to_cmd, mini->exec_args, mini->newenvp) == -1)
	{
		ft_putendl_fd("Minishell: Execve Error", 2);
		exit_fork(mini);
	}
}

int null_args(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "e"))
		return (1);
	return (0);
}