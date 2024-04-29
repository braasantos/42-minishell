/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:34 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:02:52 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_a_pipe(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (true);
	return (false);
}

bool	is_a_red(char *s)
{
	int	i;

	i = 0;
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (true);
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			return (true);
		i++;
	}
	return (false);
}

bool	is_a_append_here(char *s)
{
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (true);
	return (false);
}

bool	is_not_a_cmd(char *s, t_mini *mini)
{
	if (is_a_cmd(s, mini))
		return (true);
	if (is_a_pipe(s) && count_quotes(s) > 0)
		return (true);
	if (is_a_pipe(s) || is_a_red(s) || ft_strstartswith(s, "-")
		|| count_quotes(s) > 0 || is_a_append_here(s)
		|| is_a_file(s) || is_a_number(s))
		return (false);
	return (true);
}

bool	is_a_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			return (true);
		i++;
	}
	return (false);
}
