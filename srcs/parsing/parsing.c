/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:28 by gabe              #+#    #+#             */
/*   Updated: 2024/04/19 10:35:50 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	command(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "grep"))
		return (1);
	if (!ft_strcmp(mini->args[0], "cat"))
	{
		if (find_char('<', mini->new_str) && find_char('>', mini->new_str))
			return (0);
		else if (!find_char('<', mini->new_str) && find_char('>', mini->new_str))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	doredirect(t_mini *mini)
{
	char	**str;

	if (count_pipes(mini) == 0)
	{
		if (count_files(mini->args) > 1 && command(mini))
		{
			str = echo_w_red(mini->args);
			if (!str)
			{
				g_signal = 1;
				return (1);
			}
			ft_free_arr(mini->args);
			mini->args = get_newenvp(str);
			ft_free_arr(str);
		}
	}
	return (0);
}

int	parsing(t_mini *mini, char *str)
{
	if (!ft_check_open_quotes(str))
		return (1);
	if (!redirect_basic_check(str))
	{
		g_signal = 2;
		return (ft_fprintf(2, " syntax error near unexpected token `>'\n"), 1);
	}
	if (!pipe_check(mini, str) || im_done_parser(mini))
	{
		g_signal = 2;
		return (1);
	}
	if (check_empty(mini))
		return (ft_fprintf(2, " Is a directory\n"), 0);
	if (!mini->args[0])
		return (2);
	if (doredirect(mini))
		return (1);
	if (execute(mini))
		return (1);
	return (0);
}
