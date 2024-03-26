/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:04:44 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/26 16:32:17 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_arr(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i])
			free(str[i]);
	}
	if (str)
		free(str);
	str = NULL;
}

void	free_struct(t_mini *mini)
{
	if (mini->free_flag == 1)
		ft_free_arr(mini->echo_split);
	ft_free_arr(mini->args);
	free(mini->new_str);
	free(mini->str);
}

void	free_struct_2(t_mini *mini)
{
	if (mini->args)
		ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	exit(1);
}
