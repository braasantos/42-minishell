/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:17:19 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/02 15:48:32 by bjorge-m         ###   ########.fr       */
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
