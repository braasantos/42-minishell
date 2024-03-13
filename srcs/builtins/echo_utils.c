/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/03/13 16:55:06 by braasantos       ###   ########.fr       */
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

void check_comand(t_mini *mini)
{
	int i;
	char *temp;

	i = 0;
	if (!mini->args)
		return;
	while (mini->args[i])
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
		if (bingo(mini->args[i], '$'))
			expand_str(mini, i);
		if (bingo(mini->args[i], '\''))
			time_to_remove(mini, i);
		i++;
	}
}

char **which_split(char *str, t_mini *mini)
{
	char **split;

	split = ft_split(str, ' ');
	mini->echo_flag = 0;
	return (split);
}
int count_quote_pairs(char *str)
{
	int pairs;
	int open_quote;
	int i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			if (open_quote == 0)
				open_quote = 1;
			else
			{
				pairs++;
				open_quote = 0;
			}
		}
		i++;
	}
	return (pairs);
}