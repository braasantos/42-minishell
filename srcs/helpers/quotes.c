/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:27:14 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:27:49 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_remove_quotes(char *str)
{
	char	*new;
	int		count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	count = count_quotes(str);
	i = ft_strlen(str) - count;
	new = ft_calloc(sizeof(char), (i + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	condition_to_expand(int i, char **s)
{
	if (!ft_strcmp(s[i], "<<"))
	{
		if (s[i + 1])
		{
			if (bingo(s[i + 1], '$'))
				return (1);
		}
	}
	return (0);
}

int	bingo(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

void	remove_quotes_helper(char **str, int i)
{
	char	*temp;

	temp = ft_strdup(str[i]);
	free(str[i]);
	str[i] = ft_remove_quotes(temp);
	free(temp);
}

int	check_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
	{
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}
