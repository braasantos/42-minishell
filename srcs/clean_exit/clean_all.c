/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:04:44 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/19 13:39:38 by bjorge-m         ###   ########.fr       */
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
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	free_struct(t_mini *mini)
{
	free(mini->pwd);
	mini->pwd = NULL;
	ft_free_arr(mini->args);
	mini->args = NULL;
	free(mini->new_str);
	free(mini->str);
}

int	arg_number(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
		i++;
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
	while (ft_isdigit(*str))
	{
		number = number * 10 + *str - 48;
		str++;
	}
	return (number);
}
