/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:05:13 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/18 14:22:04 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute(t_mini *mini)
{
	int	n_pipes;

	n_pipes = count_pipes(mini);
	heredoc_first(mini, mini->args, 0);
	if (n_pipes == 0)
	{
		if (check_parser(mini) == 1 || check_here(mini) == 1)
			return (1);
		if (builtins_check(mini, 0))
			return (0);
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_child(mini, 0, 0, 0);
		free(mini->newpro);
	}
	else if ((n_pipes > 0))
	{
		if (check_parser_full(mini) == 1)
			return (1);
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_flow(mini);
		free(mini->newpro);
	}
	return (0);
}

void	create_flow(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pipe_creation(mini);
	while (mini->args[i])
	{
		if (is_not_a_cmd(mini->args[i]))
		{
			if (create_child(mini, i, 1, j) == 1)
				break ;
			j++;
		}
		if (is_not_a_cmd(mini->args[i]))
			while (mini->args[i] && ft_strcmp(mini->args[i], "|"))
				i++;
		if (mini->args[i])
			i++;
	}
	twenty_six_lines(mini);
}

int	create_child(t_mini *mini, int i, int flag, int j)
{
	mini->exit_flag = 0;
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		update_path(mini, i);
	if (null_args(mini, i))
		return (0);
	signals_child();
	mini->newpro[j] = fork();
	if (!mini->newpro[j])
	{
		through_pipes(mini, j, flag);
		if (ft_strcmp(mini->args[i], "echo"))
			if (hanlde_redirects(mini, mini->args, i, 1))
				exit_fork(mini);
		if (builtins(mini, i))
			exit_fork(mini);
		redirect(mini);
		handle_execve(mini, i);
	}
	if (mini->exit_flag != 1 && flag == 0)
		get_exit_status(mini);
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		delete_path(mini);
	return (0);
}
