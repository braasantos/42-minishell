/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:10:12 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 18:25:15 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*do_sum(t_mini *mini, int i)
{
	char	*s;

	if (count_quotes(mini->args[i + 1]) > 1)
		s = ft_remove_quotes(mini->args[i + 1]);
	else
		s = ft_strdup(mini->args[i + 1]);
	return (s);
}

int	count_quotes(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

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
int	check_position_bool(t_mini *mini, char *to_find)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], to_find))
			return (i);
		i++;
	}
	return (0);
}

int	check_position(t_mini *mini, int j)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], mini->args[j]))
			return (i);
		i++;
	}
	return (0);
}