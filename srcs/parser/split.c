/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:28:46 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:28:47 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_split_helper(t_split *split, char *str)
{
	int	len;

	split->i = 0;
	split->j = 0;
	split->start = 0;
	split->quotes = false;
	split->quote = '\0';
	split->len = 0;
	len = ft_newsplit_len(str);
	split->string = NULL;
	split->string = ft_calloc(sizeof(char *), len + 1);
}

static int	alloc_split(t_split *split, char *str, int flag)
{
	if (flag)
	{
		split->i++;
	}
	split->len = split->i - split->start;
	if (split->len > 0)
	{
		split->string[split->j] = ft_calloc(sizeof(char), (split->len + 1));
		ft_strncpy(split->string[split->j], str + split->start, split->len);
		split->j++;
	}
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

static void	ft_split_util(t_split *split, int flag, char *str)
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
		{
			split->string[split->j] = ft_calloc(sizeof(char), (split->len + 1));
			ft_strncpy(split->string[split->j], str + split->start, split->len);
			split->j++;
		}
	}
}

char	**ft_newsplit(char *str, t_split split)
{
	ft_split_helper(&split, str);
	ft_split_util(&split, 1, str);
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
			if (alloc_split(&split, str, 0))
				break ;
		}
		else if (str[split.i] && str[split.i] == split.quote
			&& split.quotes && ft_isaquote(str[split.i + 1]))
			if (alloc_split(&split, str, 1))
				break ;
		split.i++;
	}
	ft_split_util(&split, 0, str);
	split.string[split.j] = NULL;
	return (split.string);
}
