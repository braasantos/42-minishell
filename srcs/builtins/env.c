/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:23:22 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:33:24 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_envp(t_mini *mini, int j )
{
	int	i;

	i = -1;
	if (mini->args[j + 1])
	{
		if (!check_options(mini->args[++j]))
		{
			ft_fprintf(2, "Minishell: env arguments ");
			return (ft_fprintf(2, "are not supported\n"), 1);
		}
	}
	if (!mini->envp)
		return (1);
	while (mini->envp[++i])
	{
		if (bingo(mini->envp[i], '='))
			ft_printf("%s\n", mini->envp[i]);
	}
	return (1);
}

int	qmark_and_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (*str == '?')
				return (1);
			else
				return (0);
		}
		str++;
	}
	return (0);
}
