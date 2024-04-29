/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:20 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:02:15 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_fork3(t_mini *mini)
{
	if (mini->echo_split)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
	}
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->envp)
		ft_free_arr(mini->envp);
	free(mini->newpro);
	delete_path(mini);
	exit(g_signal);
}

void	exit_fork(t_mini *mini)
{
	if (mini->echo_split)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
	}
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->envp)
		ft_free_arr(mini->envp);
	free(mini->newpro);
	exit(g_signal);
}

void	ft_free_arr(char **str)
{
	int	i;

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

void	free_all(t_mini *mini)
{
	if (exit_check(mini, 0))
		return ;
	free(mini->pwd);
	mini->pwd = NULL;
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->envp)
		ft_free_arr(mini->envp);
	exit(g_signal);
}

void	free_struct(t_mini *mini)
{
	ft_free_arr(mini->args);
	mini->args = NULL;
	free(mini->new_str);
	free(mini->str);
	free(mini->pwd);
	mini->pwd = NULL;
}
