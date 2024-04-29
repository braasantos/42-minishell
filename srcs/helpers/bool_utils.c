/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:38 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:26:40 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (access(str, F_OK) == -1)
		return (free(str), false);
	return (free(str), true);
}

bool	is_a_folder(char *s)
{
	char	*str;

	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (access(str, F_OK) == -1)
		return (free(str), false);
	return (free(str), true);
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

bool	check_options(char *s)
{
	if (is_a_pipe(s) || is_a_red(s) || is_a_append_here(s))
		return (true);
	return (false);
}
