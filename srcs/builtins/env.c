/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:58:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/18 14:05:12 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_envp(t_mini *mini)
{
	int	i;

	i = -1;
	if (!mini->newenvp)
		return (1);
	while (mini->newenvp[++i])
	{
		if (bingo(mini->newenvp[i], '='))
			ft_printf("%s\n", mini->newenvp[i]);
	}
	return (1);
}
