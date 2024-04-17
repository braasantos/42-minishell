/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:04 by gabe              #+#    #+#             */
/*   Updated: 2024/04/17 15:09:06 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	have_redi(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0)
			return (1);
		if (ft_strcmp(s[i], "<") == 0)
			return (1);
		if (ft_strcmp(s[i], ">>") == 0)
			return (1);
		if (ft_strcmp(s[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	do_shlvl(t_mini *mini)
{
	int		i;
	char	*key;
	char	*value_env;
	int		value;
	char	*number;

	i = 0;
	while (mini->newenvp[i])
	{
		if (!ft_strncmp(mini->newenvp[i], "SHLVL", 5))
		{

			value_env = export_key(mini->newenvp[i]);
			value = ft_atoi(value_env);
			value++;
			key = export_var(mini->newenvp[i]);
			free(mini->newenvp[i]);
			number = ft_itoa(value);
			mini->newenvp[i] = ft_strjoin(key, number);
			free(key);
			free(value_env);
			free(number);
		}
		i++;
	}
}