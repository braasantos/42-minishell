/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/03/28 21:52:35 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char **add_option_echo(t_mini *mini, int i, char *temp)
{
	char *result;
	char *new_result;
	char **ret;

	result = NULL;
	mini->pipe_or_redirect_found = false;
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

char	**new_args(char **s, int k, int k1)
{
	char	**newenvp;
	int		i;
	int		j;
	int		len;
	int		new_index;

	len = str_len(s);
	newenvp = (char **)malloc((len + 1) * sizeof(char *));
	new_index = 0;
	i = 0;
	while (i < len)
	{
		if (i != k && i != k1)
		{
			j = ft_strlen(s[i]);
			newenvp[new_index] = (char *)malloc((j + 1) * sizeof(char));
			if (newenvp[new_index] == NULL)
				return (free(newenvp), NULL);
			ft_strcpy(newenvp[new_index], s[i]);
			new_index++;
		}
		i++;
	}
	newenvp[new_index] = NULL;
	return (newenvp);
}

int echo_w_red(t_mini *mini)
{
	int i;
	int k1;

	i = -1;
	while (mini->args[++i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
		{
			k1 = i + 1;
			mini->echo_split = new_args(mini->args, i, k1);
			mini->free_flag = 1;
			return (1);
		}
	}
	return (0);
}

void handle_split_args(t_mini *mini)
{
	int i;
	char **str;
	char *temp;

	i = -1;
	temp = NULL;
	mini->free_flag = 0;
	while (mini->args[++i])
	{
		if (!ft_strcmp(mini->args[i], "echo"))
		{
			if (count_red(mini) > 0)
				if (echo_w_red(mini))
					return;
			if (count_pipes(mini) > 0)
			{
				str = add_option_echo(mini, i, temp);
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
	}
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
		if (!have_here_doc(mini))
			if (bingo(mini->args[i], '$'))
				expand_str(mini, i);
		if (bingo(mini->args[i], '\''))
			time_to_remove(mini, i);
		i++;
	}
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
