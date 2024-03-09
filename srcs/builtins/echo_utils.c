/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/03/09 11:20:25 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	db_quotes(char *str)
{
	int	quotes;

	quotes = 0;
	while (*str)
		if (*str++ == '\"')
			quotes++;
	return (quotes);
}

bool	is_space(char c)
{
	return((c >= 9 && c <= 13) || c == 32);
}

static bool	is_echo(char *str)
{
	while (is_space(*str))
		str++;
	if (!ft_strncmp("echo", &*(str), 4))
		return (true);
	return (false);
}

char	**which_split(char *str, t_mini *mini)
{
	char	**split;

	if (is_echo(str) && db_quotes(str))
	{
		while (*str != '"')
			str++;
		split = echo_split(&*(str), '"');
		mini->echo_flag = 1;
	}
	else
	{
		split = ft_split(str, ' ');
		mini->echo_flag = 0;
	}
	return (split);
}