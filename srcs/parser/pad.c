/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:28:30 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:28:34 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pad(char *src, char *dest, int i, int j)
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

static int	check_space(char *str, int i, int pad)
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

char	*add_space(char *str)
{
	int		extra;
	char	*ret;

	if (!str)
		return (NULL);
	extra = check_space(str, 0, 0);
	if (extra == 0)
		return (ft_strdup(str));
	ret = (char *)ft_calloc(1, ft_strlen(str) + extra + 1);
	pad(str, ret, 0, 0);
	return (ret);
}
