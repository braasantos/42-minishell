/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:25 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:02:24 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	free_struct_2(t_mini *mini, int i)
{
	if (exit_check(mini, i))
		return (1);
	mini->exit_flag = 1;
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
	return (0);
}

int	get_exit_number(char *str)
{
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	while (!ft_isdigit(*str))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		number = number * 10 + *str - 48;
		str++;
	}
	return (number * sign);
}

int	is_string(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
			return (1);
		i++;
	}
	return (0);
}

int	check_exit_arguments(char **s)
{
	int	j;

	j = 1;
	while (s[j])
	{
		if (is_string(s[j]))
		{
			g_signal = 2;
			ft_fprintf(2, "Minishell: %s: numeric argument required\n", s[j]);
			return (ft_free_arr(s), 0);
		}
		if (is_a_number(s[j]))
		{
			g_signal = get_exit_number(s[j]);
			if (g_signal < 0)
				g_signal = 256 - (get_exit_number(s[j]) * -1);
			return (ft_free_arr(s), 0);
		}
		j++;
	}
	return (1);
}

bool	ft_arrayisnum(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}
