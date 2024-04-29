/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:09 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:26:10 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_fork4(t_mini *mini)
{
	if (mini->echo_split)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
	}
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->envp)
		ft_free_arr(mini->envp);
	free(mini->newpro);
	delete_path(mini);
	exit(g_signal);
}

void	handle_execve(t_mini *mini, int i)
{
	if (!is_a_cmd(mini->args[i], mini))
	{
		g_signal = 127;
		print_cmd(mini, i);
		exit_fork(mini);
	}
	if (execve(mini->path_to_cmd, mini->exec_args, mini->envp) == -1)
	{
		if (check_pwd(mini->args[0], mini))
			exit_fork(mini);
		if (!ft_strncmp(mini->args[i], "./", 2))
		{
			g_signal = 126;
			ft_fprintf(2, "Minishell: %s: Is a directory\n", mini->args[i]);
			exit_fork4(mini);
		}
		else
		{
			g_signal = 127;
			ft_fprintf(2, "Minishell: %s: command not found\n", mini->args[i]);
			exit_fork(mini);
		}
	}
}

void	get_exit_status(t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < count_pipes(mini->args) + 1)
	{
		signal(SIGINT, &sigint_on_child);
		waitpid(mini->newpro[i], &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
		i++;
	}
	if (g_signal == 131 && ft_strcmp(mini->args[0], "echo"))
		printf("Quit (core dumped)\n");
}

void	twenty_six_lines(t_mini *mini)
{
	close_pipes(mini);
	get_exit_status(mini);
}
