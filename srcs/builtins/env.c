/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:58:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/11 12:22:50 by bjorge-m         ###   ########.fr       */
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
			printf("%s\n", mini->newenvp[i]);
	}
	return (1);
}
