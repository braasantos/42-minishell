/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:51:57 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 13:52:22 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_path(t_mini *mini)
{
	if (mini->path_to_cmd)
		free(mini->path_to_cmd);
	if ((mini->exec_args))
		ft_free_arr(mini->exec_args);
}
