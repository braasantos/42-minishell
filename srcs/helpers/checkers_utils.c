/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:10:12 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/30 16:54:25 by braasantos       ###   ########.fr       */
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
