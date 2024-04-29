/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:20 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:29:24 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_dquotes(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	num_of_quotes(char *str)
{
	int		i;
	int		quote;
	char	q;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			quote++;
			i++;
			while (str[i] != q)
				i++;
			quote++;
		}
		i++;
	}
	return (quote);
}

char	*remove_quote(char *str, int i, int j, char q)
{
	char	*new;

	new = ft_calloc(sizeof(char), (ft_strlen(str) - num_of_quotes(str)) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			i++;
			while (str[i] != q)
			{
				new[j] = str[i];
				j++;
				i++;
			}
			i++;
		}
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
	}
	return (new[j] = '\0', new);
}

int	options_quotes(char *s)
{
	char	*str;

	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, "<") || !ft_strcmp(str, ">>"))
		return (free(str), 1);
	return (free(str), 0);
}

void	handle_quotes(char **s)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_arrcpy(s);
	while (s[i])
	{
		if (options_quotes(s[i]))
		{
			i++;
			continue ;
		}
		if (count_quotes(s[i]) && count_squote_pairs(s[i]) > 1)
		{
			free(s[i]);
			s[i] = remove_quote(str[i], 0, 0, '\0');
		}
		i++;
	}
	ft_free_arr(str);
}
