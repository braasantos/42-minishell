/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:28 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 14:36:44 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_files(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_a_file(s[i]))
			count++;
		i++;
	}
	return (count);
}

int	command(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "grep"))
		return (1);
	if (!ft_strcmp(mini->args[0], "cat"))
		return (1);
	return (0);
}

int	doredirect(t_mini *mini)
{
	char	**str;

	if (count_files(mini->args) > 1 && command(mini))
	{
		str = echo_w_red(mini->args);
		if (!str)
			return (1);
		ft_free_arr(mini->args);
		mini->args = get_newenvp(str);
		ft_free_arr(str);
	}
	return (0);
}

int	parsing(t_mini *mini, char *str)
{
	if (!ft_check_open_quotes(str))
		return (1);
	if (!redirect_basic_check(str))
		return (ft_putendl_fd(" syntax error near unexpected token `>'", 2), 1);
	if (!pipe_check(mini, str))
	{
		g_signal = 2;
		return (1);
	}
	if (naaaaaaaaaaaa(mini))
		return (ft_putendl_fd(" Is a directory", 2), 0);
	if (!mini->args[0])
		return (2);
	if (doredirect(mini))
		return (1);
	if (execute(mini))
		return (1);
	return (0);
}
