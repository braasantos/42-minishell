/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:27:04 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:27:05 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_open_quotes(char *str)
{
	char	quote;
	int		state;

	state = 0;
	while (*str)
	{
		if (!state && (*str == '\'' || *str == '\"'))
		{
			state = 1;
			quote = *str;
		}
		else if (state && *str == quote)
			state = 0;
		str++;
	}
	if (state && write(2, "Minishell: Error: Open quotes\n", 31))
	{
		g_signal = 2;
		return (0);
	}
	return (1);
}

int	redirect_check(char *str)
{
	int	i;
	int	count;

	i = -1;
	while (str[++i])
	{
		count = 0;
		if (find_char(str[i], "><") && !quotes_open(str, i))
		{
			while (str[i] && find_char(str[i], "><"))
			{
				if (find_char(str[i + 1], "><") && str[i + 1] != str[i])
					return (0);
				count++;
				i++;
			}
		}
		if (count > 2)
			return (0);
	}
	return (1);
}

int	count_all_pipes(char *s)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '|')
			count++;
		i++;
	}
	if (count == ft_strlen(s) && ft_strlen(s) > 1)
		return (1);
	return (0);
}

int	pipe_check(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (count_all_pipes(str[i]))
		{
			ft_fprintf(2, "Minishell: syntax error");
			ft_fprintf(2, " near unexpected token `||'\n");
			return (1);
		}
	}
	return (0);
}
