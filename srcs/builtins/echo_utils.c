/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/03/12 14:56:52 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool db_quotes(char *str)
{
	int quotes;

	quotes = 0;
	while (*str)
		if (*str++ == '\"')
			quotes++;
	return (quotes);
}

bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool is_echo(char *str)
{
	if (!str)
		return (NULL);
	while (is_space(*str))
		str++;
	if (!ft_strncmp("echo", &*(str), 4))
		return (true);
	return (false);
}

void check_comand(t_mini *mini)
{
	int i;
	char *temp;

	i = 0;
	if (!mini->args)
		return ;
	while(mini->args[i])
	{
		if (is_a_cmd(mini->args[i], mini))
		{
			if (count_quotes(mini->args[i]) > 0)
			{
				temp = ft_strdup(mini->args[i]);
				free(mini->args[i]);
				mini->args[i] = ft_remove_quotes(temp);
				free(temp);
			}
		}
		i++;
	}
}

char **which_split(char *str, t_mini *mini)
{
	char **split;

	if (is_echo(str) && db_quotes(str))
	{
		while (*str != '"' && *str != '-')
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
