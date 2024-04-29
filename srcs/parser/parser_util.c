/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:28:42 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:28:43 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	checking(t_mini *mini)
{
	if (parser_util(mini->new_str))
		return (1);
	if (handle_tokens(mini))
		return (1);
	return (0);
}

int	parser_util(char *str)
{
	if (ft_isspace(str))
		return (1);
	if (!ft_check_open_quotes(str))
		return (1);
	if (!redirect_check(str))
	{
		g_signal = 2;
		return (ft_fprintf(2, " syntax error near unexpected token `>'\n"), 1);
	}
	return (0);
}

int	command(t_mini *mini, char **s)
{
	if (!ft_strcmp(s[0], "grep"))
		return (1);
	if (!ft_strcmp(s[0], "cat"))
	{
		if (find_char('<', mini->new_str) && find_char('>', mini->new_str))
			return (0);
		else if (!find_char('<', mini->new_str)
			&& find_char('>', mini->new_str))
			return (0);
		else
			return (1);
	}
	return (0);
}
