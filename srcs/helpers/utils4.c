/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:17:19 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/18 20:43:49 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	while_loop(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_printf("%s\n", s[i]);
		i++;
	}
}

char	*ft_touppercase(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - ('a' - 'A');
		i++;
	}
	return (s);
}

int	print_error(char *s)
{
	if (!ft_strcmp(s, ">"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'", 2);
		return (1);
	}
	return (0);
}

int	check_next(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], ">")
		|| (!ft_strcmp(mini->args[i], "<"))
		|| is_a_append_here(mini->args[i]))
	{
		if (mini->args[i + 1])
			return (1);
	}
	return (0);
}
