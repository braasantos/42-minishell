/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:59 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:27:00 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_files(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_a_file(s[i]))
			count++;
		i++;
	}
	return (count);
}

int	ft_isspace(char *s)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
			count++;
		i++;
	}
	if (count == ft_strlen(s))
		return (1);
	return (0);
}

int	find_char(char c, char *find)
{
	int	i;

	i = -1;
	while (find[++i])
		if (find[i] == c)
			return (1);
	return (0);
}

int	pipe_or_append(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (1);
	if (!ft_strcmp(s, ">>"))
		return (1);
	return (0);
}

int	get_grep(t_mini *mini, int i)
{
	i++;
	if (mini->args[i])
		i++;
	if (!mini->args[i])
		return (0);
	if (is_a_red(mini->args[i]))
		i++;
	while (mini->args[i])
	{
		if (!is_a_file(mini->args[i]))
		{
			ft_fprintf(2, "Minishell: No such file or directory\n");
			g_signal = 2;
			return (1);
		}
		i++;
	}
	return (0);
}
