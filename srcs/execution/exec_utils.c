/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:09:09 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 18:42:01 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_execve(t_mini *mini, int i)
{
	if (!is_a_cmd(mini->args[i], mini))
	{
		print_cmd(mini, i);
		exit_fork(mini);
	}
	if (execve(mini->path_to_cmd, mini->exec_args, mini->newenvp) == -1)
	{
		if (ft_strchr(mini->args[i], '/'))
		{
			g_signal = 126;
			ft_putstr_fd(mini->args[i], 2);
			ft_putendl_fd(": Is a directory", 2);
		}
		else
		{
			g_signal = 127;
			ft_putstr_fd(mini->args[i], 2);
			ft_putendl_fd(": command not found", 2);
		}
		exit_fork(mini);
	}
}

void	get_exit_status(t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < count_pipes(mini) + 1)
	{
		signal(SIGINT, &sigint_on_child);
		waitpid(mini->newpro[i], &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
		i++;
	}
}

int	null_args(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "e"))
		return (1);
	return (0);
}

void	twenty_six_lines(t_mini *mini)
{
	close_pipes(mini);
	get_exit_status(mini);
}

void	exit_fork(t_mini *mini)
{
	if (mini->echo_split)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
	}
	unlink(".heredoc");
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	free(mini->newpro);
	exit(g_signal);
}