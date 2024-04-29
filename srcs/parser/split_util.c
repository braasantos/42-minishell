/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:28:51 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:28:52 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isaquote(char c)
{
	if (!c)
		return (1);
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

static void	ft_split_helper_len(t_split *split)
{
	split->i = 0;
	split->j = 0;
	split->start = 0;
	split->quotes = false;
	split->quote = '\0';
	split->len = 0;
}

static int	alloc_split_len(t_split *split, char *str, int flag)
{
	if (flag)
	{
		split->i++;
	}
	split->len = split->i - split->start;
	if (split->len > 0)
		split->j++;
	while (str[split->i] && (str[split->i] == ' '
			|| str[split->i] == 10 || str[split->i] == 9))
		split->i++;
	split->start = split->i;
	if (!str[split->i])
		return (1);
	split->i--;
	if (flag)
		split->quotes = false;
	return (0);
}

static void	ft_split_util_len(t_split *split, int flag, char *str)
{
	if (flag)
	{
		while (str[split->i] && (str[split->i] == ' '
				|| str[split->i] == 10 || str[split->i] == 9))
			split->i++;
	}
	else
	{
		split->len = split->i - split->start;
		if (split->len > 0)
			split->j++;
	}
}

int	ft_newsplit_len(char *str)
{
	t_split	split;

	ft_split_helper_len(&split);
	ft_split_util_len(&split, 1, str);
	split.start = split.i;
	while (str[split.i])
	{
		if ((str[split.i] == '\'' || str[split.i] == '\"') && !split.quotes)
		{
			split.quotes = true;
			split.quote = str[split.i];
		}
		else if (str[split.i] && str[split.i] == ' ' && !split.quotes)
		{
			if (alloc_split_len(&split, str, 0))
				break ;
		}
		else if (str[split.i] && str[split.i] == split.quote
			&& split.quotes && ft_isaquote(str[split.i + 1]))
			if (alloc_split_len(&split, str, 1))
				break ;
		split.i++;
	}
	ft_split_util_len(&split, 0, str);
	return (split.j);
}
