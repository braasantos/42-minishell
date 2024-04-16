/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:11:21 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 14:11:54 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_child(t_mini *mini, int i, int flag, int j)
{
	mini->exit_flag = 0;
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		update_path(mini, i);
	if (null_args(mini, i))
		return (0);
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
