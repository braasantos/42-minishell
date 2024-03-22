/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:40:05 by gabe              #+#    #+#             */
/*   Updated: 2024/03/21 12:57:11 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_countword(char const *s, char c)
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else
		{
			if (!flag)
			{
				count++;
				flag = 1;
			}
		}
		s++;
	}
	return (count);
}

static int	ft_free(char **new_arr, int count)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < count)
		if (!new_arr[i++])
			flag = 1;
	if (flag)
	{
		i = 0;
		while (i < count)
			free(new_arr[i++]);
		free(new_arr);
		return (0);
	}
	return (1);
}

static char	**ft_putwords(char **new, char const *s, char c)
{
	char	**newarr;
	int		flag;
	int		count;

	newarr = new;
	flag = 0;
	count = 0;
	newarr[count++] = ft_strdup("echo");
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else
		{
			if (!flag)
			{
				newarr[count] = ft_substr(s, 0, ft_strchr(s, c) - s);
				flag = 1;
				count++;
			}
		}
		s++;
	}
	newarr[count] = NULL;
	return (newarr);
}

char	**echo_split(char const *s, char c)
{
	char	**new_arr;
	int		count;

	if (!s)
		return (NULL);
	count = ft_countword(s, c) + 1;
	new_arr = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!new_arr)
		return (NULL);
	ft_putwords(new_arr, s, c);
	if (!ft_free(new_arr, count))
		return (NULL);
	return (new_arr);
}
