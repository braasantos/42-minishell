/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:04:44 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/10 16:26:31 by bjorge-m         ###   ########.fr       */
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

int	arg_number(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
		i++;
	if (i > 2)
	{
		g_signal = 1;
		ft_putstr_fd(" too many arguments\n", 2);
	}
	return (i);
}

int	check_signals(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '-')
		{
			g_signal = 156;
			return (1);
		}
	}
	return (0);
}

int	get_exit_number(char *str)
{
	int	number;
	
	number = 0;
	while (!ft_isdigit(*str))
		str++;
	while(ft_isdigit(*str))
	{
		number = number * 10 + *str - 48;
		str++;
	}
	return (number);
}

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

void free_struct_2(t_mini *mini)
{
	if (exit_check(mini))
		return ;
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
