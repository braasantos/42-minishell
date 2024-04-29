/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:16 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:29:45 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_remove_dquotes(const char *str)
{
	char	*new_str;
	size_t	len;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (new_str == NULL)
		return (NULL);
	while (i < len)
	{
		if (str[i] != '\"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	count_dquote_pairs(char *str)
{
	int	pairs;
	int	open_quote;
	int	i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			if (open_quote == 0)
				open_quote = 1;
			else
			{
				pairs++;
				open_quote = 0;
			}
		}
		i++;
	}
	return (pairs);
}

int	count_squote_pairs(char *str)
{
	int	pairs;
	int	open_quote;
	int	i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (open_quote == 0)
				open_quote = 1;
			else
			{
				pairs++;
				open_quote = 0;
			}
		}
		i++;
	}
	return (pairs);
}

char	*ft_remove_squotes(const char *str)
{
	char	*new_str;
	size_t	len;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (new_str == NULL)
		return (NULL);
	while (i < len)
	{
		if (str[i] != '\'')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	remove_d_quotes(char **str, int i, char *s)
{
	int	d_quotes;
	int	s_quotes;

	d_quotes = count_dquote_pairs(str[i]);
	s_quotes = count_squote_pairs(str[i]);
	if (d_quotes > 0 && s_quotes > 0)
	{
		if (d_quotes % 2 == 0)
		{
			s = ft_remove_dquotes(str[i]);
			free(str[i]);
			str[i] = ft_strdup(s);
			free(s);
		}
		else if (d_quotes % 2 != 0)
		{
			s = ft_remove_squotes(str[i]);
			free(str[i]);
			str[i] = ft_strdup(s);
			free(s);
		}
	}
}
