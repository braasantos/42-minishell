/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:51:12 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/29 17:03:38 by braasantos       ###   ########.fr       */
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

int	builtins(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
	{
		mini->exit_flag = 1;
		unlink(".heredoc");
		free_struct_2(mini);
	}
	if (!ft_strcmp(mini->args[i], "pwd"))
		return (print_pwd());
	if (!ft_strcmp(mini->args[i], "echo"))
		return (echo_cmd(mini->echo_split, mini));
	if ((!ft_strcmp(mini->args[i], "cd")))
		return (get_cd(mini, i));
	if ((!ft_strcmp(mini->args[i], "env")))
		return (get_envp(mini));
	if ((!ft_strcmp(mini->args[i], "export")))
		return (get_export(mini));
	if ((!ft_strcmp(mini->args[i], "unset")))
		return (get_unset(mini));
	return (0);
}

int	check_parser2(t_mini *mini, int i)
{
	int	file_fd;

	file_fd = 0;
	file_fd = open(mini->args[i], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (1);
	}
	return (0);
}

bool	is_a_builtin(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
		return (true);
	if (!ft_strcmp(mini->args[i], "pwd"))
		return (true);
	if (!ft_strcmp(mini->args[i], "echo"))
		return (true);
	if ((!ft_strcmp(mini->args[i], "cd")))
		return (true);
	if ((!ft_strcmp(mini->args[i], "env")))
		return (true);
	if ((!ft_strcmp(mini->args[i], "export")))
		return (true);
	if ((!ft_strcmp(mini->args[i], "unset")))
		return (true);
	return (false);
}
