/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:13:10 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 14:13:37 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_check(t_mini *mini)
{
	if (arg_number(mini) > 2)
		return (1);
	if (arg_number(mini) == 2)
	{
		if (ft_isalpha(mini->args[1][0]))
		{
			g_signal = 2;
			ft_putstr_fd(" numeric argument required\n", 2);
			return (1);
		}
		if (check_signals(mini->args[1]))
			return (1);
		if (is_a_number(mini->args[1]))
		{
			g_signal = get_exit_number(mini->args[1]) % 256;
			return (1);
		}
	}
	return (0);
}

void	free_struct_2(t_mini *mini)
{
	if (exit_check(mini))
		return ;
	mini->exit_flag = 1;
	unlink(".heredoc");
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	exit(0);
}
