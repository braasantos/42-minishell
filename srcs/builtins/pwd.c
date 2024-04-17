/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:03:47 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 18:18:47 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd(t_mini *mini)
{
	int		i;

	if (mini->pwd)
	{
		free(mini->pwd);
		mini->pwd = NULL;
	}
	i = -1;
	while (mini->newenvp[++i])
	{
		if (!ft_strncmp(mini->newenvp[i], "PWD", 3))
			mini->pwd = export_key(mini->newenvp[i]);
	}
	if (!mini->pwd)
	{
		mini->pwd = getcwd(0, 0);
		return ;
	}
}

int	print_pwd(t_mini *mini)
{
	ft_printf("%s\n", mini->pwd);
	return (1);
}
