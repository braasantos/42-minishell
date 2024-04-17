/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:51:12 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/17 16:41:09 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pre_echo(t_mini *mini, int i)
{
	if (handle_split_args(mini, i))
		return (1);
	check_echo(mini);
	return (0);
}

int	builtins(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
		free_struct_2(mini);
	if (!ft_strcmp(mini->args[i], "pwd"))
		return (print_pwd(mini));
	if (!ft_strcmp(mini->args[i], "echo"))
	{
		if (pre_echo(mini, i))
			return (1);
		return (echo_cmd(mini->echo_split, mini));
	}
	if ((!ft_strcmp(mini->args[i], "cd")))
		return (get_cd(mini, i));
	if ((!ft_strcmp(mini->args[i], "env")))
		return (get_envp(mini));
	if ((!ft_strcmp(mini->args[i], "export")))
	{
		if (check_env(mini))
			return (1);
		return (get_export(mini));
	}
	if ((!ft_strcmp(mini->args[i], "unset")))
		return (get_unset(mini));
	return (0);
}

void	ft_exit_builtin(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
	{
		mini->exit_flag = 1;
		unlink(".heredoc");
		free_struct_2(mini);
	}
}

int	builtins_check(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
	{
		free_struct_2(mini);
		return (1);
	}
	if (!ft_strcmp(mini->args[i], "pwd"))
		return (print_pwd(mini));
	if ((!ft_strcmp(mini->args[i], "cd")))
		return (get_cd(mini, i));
	if ((!ft_strcmp(mini->args[i], "env")))
		return (get_envp(mini));
	if ((!ft_strcmp(mini->args[i], "export"))
		|| (!ft_strcmp(mini->args[i], "unset")))
		if (check_env(mini))
			return (1);
	if ((!ft_strcmp(mini->args[i], "export")))
		return (get_export(mini));
	if ((!ft_strcmp(mini->args[i], "unset")))
		return (get_unset(mini));
	if (!ft_strcmp(mini->args[i], "grep"))
	{
		if (get_grep(mini, i))
			return (1);
	}
	return (0);
}
