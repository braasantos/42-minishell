/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:57:55 by gabe              #+#    #+#             */
/*   Updated: 2024/04/19 11:30:49 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_dquote_pairs(char *str)
{
	int	pairs;
	int	open_quote;
	int	i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
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

int	count_squote_pairs(char *str)
{
	int	pairs;
	int	open_quote;
	int	i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
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

int	condition_to_expand(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "<<"))
	{
		if (mini->args[i + 1])
		{
			if (bingo(mini->args[i + 1], '$'))
				return (1);
		}
	}
	if (bingo(mini->args[i], '\'') && !bingo(mini->args[i], '$'))
		time_to_remove(mini, i);
	return (0);
}

int	check_things(char *s)
{
	char *str;

	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (!ft_strcmp(str, ">"))
		return (free(str), 1);
	if (!ft_strcmp(str, "<"))
		return (free(str), 1);
	if (!ft_strcmp(str, "|"))
		return (free(str), 1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (free(str), 1);
	return (free(str), 0);
}

void	take_care(t_mini *mini, int flag, char **s)
{
	if (flag)
	{
		if (mini->echo_split)
		{
			ft_free_arr(mini->echo_split);
			mini->echo_split = NULL;
		}
		mini->echo_split = get_newenvp(s);
	}
	if (!flag)
	{
		if (mini->args)
		{
			ft_free_arr(mini->args);
			mini->args = NULL;
		}
		mini->args = get_newenvp(s);
	}
}
