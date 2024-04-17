/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:40:05 by gabe              #+#    #+#             */
/*   Updated: 2024/04/17 11:04:21 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_strncpy(char *dest, const char *src, size_t num)
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

static void	init_split(t_split *split, char *str)
{
	int	len;

	split->i = 0;
	split->start = 0;
	split->words = 0;
	split->temp = ft_split(str, ' ');
	len = export_len(split->temp);
	ft_free_arr(split->temp);
	split->quotes = false;
	split->s = (char **)malloc((len + 1) * sizeof(char *));
}

static char	**return_split(t_split *split, char *str)
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
	return (split->s);
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

char	**new_split(char *str)
{
	t_split	split;

	init_split(&split, str);
	while (str[split.i])
	{
		if (count_quotes(str) > 0)
			middle_split(&split, str);
		else
		{
			if (str[split.i] == ' ')
			{
				return_split(&split, str);
				split.start = split.i + 1;
			}
		}
		split.i++;
	}
	return (return_split(&split, str));
}
