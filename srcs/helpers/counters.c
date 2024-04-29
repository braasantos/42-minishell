/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:43 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:26:46 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	arr_len(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

int	count_squotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	count_red(t_mini *mini)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "<") == 0
			|| ft_strcmp(mini->args[i], ">") == 0
			|| !ft_strcmp(mini->args[i], ">>"))
			count++;
		i++;
	}
	return (count);
}

int	count_pipes(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], "|"))
			count++;
		i++;
	}
	return (count);
}
