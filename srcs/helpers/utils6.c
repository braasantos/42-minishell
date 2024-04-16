/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:04 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 18:48:27 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	have_redi(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0)
			return (1);
		if (ft_strcmp(s[i], "<") == 0)
			return (1);
		if (ft_strcmp(s[i], ">>") == 0)
			return (1);
		if (ft_strcmp(s[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}