/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:51:12 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 16:20:09 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	str_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	have_redirect(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], ">") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], "<") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], ">>") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	have_here_doc(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

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
