/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:40:05 by gabe              #+#    #+#             */
/*   Updated: 2024/04/19 13:53:04 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_space(char *s)
{
	int	i;
	size_t count;

	i = 0;
	count = 0;
	while(s[i])
	{
		if (s[i] == 9 || s[i] == 10 || s[i] == 32)
			count++;
		i++;
	}
	if (count == ft_strlen(s))
		return (1);
	return (0);
}

static int	init_split(t_split *split, char *str)
{
	int	len;

	split->i = 0;
	split->start = 0;
	split->words = 0;
	split->quotes = false;
	if (ft_is_space(str))
		return (1);
	split->temp = ft_split(str, ' ');
	if (count_quotes(str))
		len = 100;
	else
		len = str_len(split->temp);
	ft_free_arr(split->temp);
	split->s = (char **)malloc((len + 1) * sizeof(char *));
	return (0);
}

static void	last_split(t_split *split, char *str)
{
	split->tokens = split->i - split->start;
	if (split->tokens > 0)
	{
		split->s[split->words] = (char *)
			malloc((split->tokens + 1) * sizeof(char));
		ft_strncpy(split->s[split->words], &str[split->start], split->tokens);
		split->words++;
	}
	split->s[split->words] = NULL;

}

static void	return_split(t_split *split, char *str)
{
	split->tokens = split->i - split->start;
	if (split->tokens > 0)
	{
		split->s[split->words] = (char *)
			malloc((split->tokens + 1) * sizeof(char));
		ft_strncpy(split->s[split->words], &str[split->start], split->tokens);
		split->words++;
	}
}

static void	middle_split(t_split *split, char *str)
{
	if (count_dquotes(str) > 1)
	{
		if (str[split->i] == '\"')
			split->quotes = !split->quotes;
		else if (str[split->i] == ' ' && !split->quotes)
		{
			return_split(split, str);
			split->start = split->i + 1;
		}
	}
	else if (count_squotes(str) > 1)
	{
		if (str[split->i] == '\'')
			split->quotes = !split->quotes;
		else if (str[split->i] == ' ' && !split->quotes)
		{
			return_split(split, str);
			split->start = split->i + 1;
		}
	}
}

int	new_split(char *str, t_mini *mini)
{
	t_split	split;

	if (init_split(&split, str))
		return (1);
	while (str[split.i])
	{
		if (count_quotes(str) > 0)
			middle_split(&split, str);
		else
		{
			if (str[split.i] == ' ' || str[split.i] == 9 || str[split.i] == 10)
			{
				return_split(&split, str);
				split.start = split.i + 1;
			}
		}
		split.i++;
	}
	last_split(&split, str);
	if (mini->args)
		ft_free_arr(mini->args);
	mini->args = get_newenvp(split.s);
	if (split.s)
		ft_free_arr(split.s);
	return (0);
}
