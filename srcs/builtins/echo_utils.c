/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/03/15 20:16:47 by braasantos       ###   ########.fr       */
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

char **add_option_echo(t_mini *mini, int i)
{
	char *temp;
	char *result;
	char *new_result;
	char **ret;

	result = NULL;
	while (mini->args[i] && !mini->pipe_or_redirect_found)
	{
		temp = hndl_quotes(mini, i);
		if (result == NULL)
			result = ft_strdup(temp);
		else
		{
			if (save_lines2(mini, temp, i))
				break;
			new_result = ft_strjoin(result, temp);
			free(result);
			result = ft_strdup(new_result);
			free(new_result);
		}
		free(temp);
		i++;
	}
	ret = ft_split(result, ' ');
	return (free(result), ret);
}
void handle_split_args(t_mini *mini)
{
	int i;
	char **str;

	i = 0;
	mini->free_flag = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], "echo"))
		{
			if (count_pipes(mini) > 0 || count_red(mini) > 0)
			{
				str = add_option_echo(mini, i);
				mini->echo_split = get_newenvp(str);
				ft_free_arr(str);
				mini->free_flag = 1;
			}
			else
			{
				mini->echo_split = get_newenvp(mini->args);
				mini->free_flag = 1;
			}
		}
		i++;
	}
	ft_printf("%d\n", mini->free_flag);
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