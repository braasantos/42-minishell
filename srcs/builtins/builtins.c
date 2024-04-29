/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:22:00 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:03:04 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	pre_echo(t_mini *mini, int i)
{
	if (handle_split_args(mini, i))
		return (1);
	check_echo(mini);
	return (0);
}

int	builtins_utils(t_mini *mini, int i)
{
	if ((!ft_strcmp(mini->args[i], "env"))
		|| !ft_strcmp(mini->args[i], "\\env"))
		return (get_envp(mini, i), 1);
	if ((!ft_strcmp(mini->args[i], "export"))
		|| !ft_strcmp(mini->args[i], "\\export"))
	{
		if (check_env(mini))
			return (1);
		return (get_export(mini), 1);
	}
	if ((!ft_strcmp(mini->args[i], "unset"))
		|| !ft_strcmp(mini->args[i], "\\unset"))
		return (get_unset(mini), 1);
	return (0);
}

int	builtins2(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit")
		|| !ft_strcmp(mini->args[i], "\\exit"))
		if (free_struct_2(mini, i))
			return (1);
	if (!ft_strcmp(mini->args[i], "pwd")
		|| !ft_strcmp(mini->args[i], "\\pwd"))
		return (print_pwd(mini));
	if (!ft_strcmp(mini->args[i], "echo")
		|| !ft_strcmp(mini->args[i], "\\echo"))
	{
		if (pre_echo(mini, i))
			return (1);
		return (echo_cmd(mini->echo_split, mini));
	}
	if ((!ft_strcmp(mini->args[i], "cd"))
		|| !ft_strcmp(mini->args[i], "\\cd"))
		return (get_cd(mini, i));
	if (builtins_utils(mini, i))
		return (1);
	return (0);
}

int	builtins(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit")
		|| !ft_strcmp(mini->args[i], "\\exit"))
	{
		free_all(mini);
		return (1);
	}
	if (!ft_strcmp(mini->args[i], "pwd")
		|| !ft_strcmp(mini->args[i], "\\pwd"))
		return (print_pwd(mini));
	if ((!ft_strcmp(mini->args[i], "cd")) || !ft_strcmp(mini->args[i], "\\cd"))
		return (get_cd(mini, i));
	if ((!ft_strcmp(mini->args[i], "env"))
		|| !ft_strcmp(mini->args[i], "\\env"))
		return (get_envp(mini, i));
	if ((!ft_strcmp(mini->args[i], "export"))
		|| !ft_strcmp(mini->args[i], "\\export"))
	{
		if (check_env(mini))
			return (1);
		return (get_export(mini), 1);
	}
	if ((!ft_strcmp(mini->args[i], "unset"))
		|| !ft_strcmp(mini->args[i], "\\unset"))
		return (get_unset(mini));
	return (0);
}

bool	is_a_builtin(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit")
		|| !ft_strcmp(mini->args[i], "\\exit"))
		return (true);
	if (!ft_strcmp(mini->args[i], "pwd")
		|| !ft_strcmp(mini->args[i], "\\pwd"))
		return (true);
	if (!ft_strcmp(mini->args[i], "echo")
		|| !ft_strcmp(mini->args[i], "\\echo"))
		return (true);
	if ((!ft_strcmp(mini->args[i], "cd"))
		|| !ft_strcmp(mini->args[i], "\\cd"))
		return (true);
	if ((!ft_strcmp(mini->args[i], "env"))
		|| !ft_strcmp(mini->args[i], "\\env"))
		return (true);
	if ((!ft_strcmp(mini->args[i], "export"))
		|| !ft_strcmp(mini->args[i], "\\export"))
		return (true);
	if ((!ft_strcmp(mini->args[i], "unset"))
		|| !ft_strcmp(mini->args[i], "\\unset"))
		return (true);
	return (false);
}
