/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:04 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 13:53:27 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
