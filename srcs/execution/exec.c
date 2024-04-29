/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:05 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 12:54:00 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_helper(t_mini *mini, int flag)
{
	if (flag)
	{
		if (check_options(mini->args[0]))
			return (1);
		if (!ft_strcmp(mini->args[0], "grep"))
			if (get_grep(mini, 0))
				return (2);
	}
	else
	{
		if (check_all_redirects(mini->args) == 2)
			return (2);
		if (is_a_pipe(mini->args[0]))
			return (g_signal = 2, 1);
	}
	return (0);
}

int	execute(t_mini *mini)
{
	int	n_pipes;

	n_pipes = count_pipes(mini->args);
	if (count_pipes(mini->args) == 0)
	{
		if (check_all_redirects(mini->args))
			return (0);
		if (count_red(mini) == 0)
			if (builtins(mini, 0))
				return (0);
		if (execute_helper(mini, 1) == 2)
			return (1);
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_child(mini, 0, 0, 0);
		free(mini->newpro);
	}
	else
	{
		if (execute_helper(mini, 0))
			return (1);
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_flow(mini);
		free(mini->newpro);
	}
	return (0);
}

int	create_child(t_mini *mini, int i, int flag, int j)
{
	mini->exit_flag = 0;
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		update_path(mini, i);
	signals_child();
	mini->newpro[j] = fork();
	if (!mini->newpro[j])
	{
		if (which_first(mini, i, j, flag))
			exit_fork3(mini);
		if (builtins2(mini, i))
			exit_fork(mini);
		handle_execve(mini, i);
	}
	redirect(mini);
	ft_ignore_signals();
	if (mini->exit_flag != 1 && flag == 0)
		get_exit_status(mini);
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		delete_path(mini);
	ft_init_signals();
	return (0);
}

int	which_first(t_mini *mini, int i, int j, int flag)
{
	if (red_in(mini))
	{
		handle_pipes(mini, j, flag);
		if (ft_strcmp(mini->args[i], "echo"))
			if (hanlde_redirects(mini, mini->args, i))
				return (1);
	}
	else if (count_red(mini) == 0)
		handle_pipes(mini, j, flag);
	else if (red_out(mini))
	{
		if (ft_strcmp(mini->args[i], "echo"))
			if (hanlde_redirects(mini, mini->args, i))
				return (1);
		handle_pipes(mini, j, flag);
	}
	return (0);
}

void	create_flow(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	create_pipes(mini);
	while (mini->args[i])
	{
		if (is_not_a_cmd(mini->args[i], mini))
		{
			if (create_child(mini, i, 1, j) == 1)
				break ;
			j++;
		}
		if (is_not_a_cmd(mini->args[i], mini))
			while (mini->args[i] && ft_strcmp(mini->args[i], "|"))
				i++;
		if (mini->args[i])
			i++;
	}
	twenty_six_lines(mini);
}
