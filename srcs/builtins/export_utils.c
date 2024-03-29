/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:03:18 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/29 15:18:43 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	fore(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (s[i] == ' ')
		i++;
	return (i);
}

int	afta(char *s)
{
	int	j;
	int	i;

	j = 0;
	i = fore(s);
	while (s[i++] && s[i] != '=')
		j++;
	if (s[i++] == '=')
		j++;
	return (j);
}

char	*help(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*s;

	j = afta(str);
	s = malloc(sizeof(char) * (j + 2));
	k = fore(str);
	i = 0;
	while (str[k])
	{
		s[i++] = str[k];
		k++;
	}
	s[j] = '=';
	s[j + 1] = '\0';
	return (s);
}

int	ft_before_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}
