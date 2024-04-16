/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:06:11 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 14:06:41 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_parser2(t_mini *mini, int i)
{
	int		file_fd;
	char	*s;

	if (count_quotes(mini->args[i]))
		s = ft_remove_quotes(mini->args[i]);
	else
		s = ft_strdup(mini->args[i]);
	file_fd = 0;
	if (access(s, W_OK) == -1)
		return (free(s), 1);
	if (check_options(s))
	{
		g_signal = 1;
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (free(s), 1);
	}
	file_fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!file_fd)
	{
		g_signal = 1;
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (free(s), 1);
	}
	return (free(s), 0);
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
