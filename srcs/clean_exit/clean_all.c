/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:04:44 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/06 17:33:48 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_free_arr(char **str)
{
	int i;

	if (!str || !*str)
		return ;
	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	free_struct(t_mini *mini)
{
	if (mini->echo_flag)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_flag = 0;
	}
	mini->flag_echo = 0;
	ft_free_arr(mini->args);
	free(mini->new_str);
	free(mini->str);
}

void free_struct_2(t_mini *mini)
{
	mini->exit_flag = 1;
	unlink(".heredoc");
	if (mini->echo_flag)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_flag = 0;
	}
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	exit(0);
}
