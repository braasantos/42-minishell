/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:09:37 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/08 18:11:07 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_a_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

bool	is_a_red(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			return (true);
		i++;
	}
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (true);
	return (false);
}

bool	is_a_quote(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			count++;
		i++;
	}
	if (count == i)
		return (true);
	return (false);
}

bool	is_a_cmd(char *s, t_mini *mini)
{
	char	*str;
	char	*temp;
	bool	result;

	result = false;
	if (is_a_quote(s))
		return (result);
	if (count_quotes(mini->new_str) > 0)
		temp = ft_remove_quotes(s);
	else
		temp = ft_strdup(s);
	str = ft_add(mini, temp);
	if (!str)
	{
		free(temp);
		return (false);
	}
	if (str)
	{
		if (access(str, X_OK) == 0)
			result = true;
		free(str);
	}
	free(temp);
	return (result);
}

bool	is_a_file(char *s)
{
	char	*str;

	if (count_quotes(s))
		str =ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (access(str, R_OK) == -1)
		return (free(str), false);
	return (free(str), true);
}

bool	is_a_option(char *s, t_mini *mini)
{
	char	*str;

	if (is_a_pipe(s) || is_a_red(s) || is_a_file(s))
		return (false);
	if (!ft_strcmp(s, "-"))
		return (true);
	str = ft_add(mini, s);
	if (access(str, X_OK) == -1)
		return (free(str), true);
	else
		return (free(str), false);
}
