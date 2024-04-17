/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:12:30 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 18:24:58 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pad(char *src, char *dest, int i, int j)
{
	char	skip;

	while (src[i])
	{
		if (src[i] && find_char(src[i], "|><") && !quotes_open(src, i))
		{
			dest[j++] = ' ';
			skip = src[i];
			while (src[i] == skip)
				dest[j++] = src[i++];
			dest[j++] = ' ';
			continue ;
		}
		dest[j++] = src[i];
		i++;
	}
}

int	padding_needed(char *str, int i, int pad)
{
	char	skip;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] && find_char(str[i], "|><") && !quotes_open(str, i))
		{
			skip = str[i];
			while (str[i] && str[i] == skip)
				i++;
			pad += 2;
			continue ;
		}
		i++;
	}
	return (pad);
}

char	*pad_central(char *str)
{
	int		extra;
	char	*ret;

	if (!str)
		return (NULL);
	extra = padding_needed(str, 0, 0);
	if (extra == 0)
		return (ft_strdup(str));
	ret = (char *)ft_calloc(1, ft_strlen(str) + extra + 1);
	pad(str, ret, 0, 0);
	return (ret);
}
