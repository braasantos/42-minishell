/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:54:56 by gabe              #+#    #+#             */
/*   Updated: 2024/04/17 13:42:51 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	has_two_args(char **args, t_mini *mini)
{
	if (args[1])
	{
		if (args[2])
		{
			ft_fprintf(2, "cd: too many arguments\n");
			g_signal = 1;
			return (1);
		}
		if (!ft_strcmp(args[1], "-"))
			print_pwd(mini);
		else
			change_dir(args[1], mini);
		return (1);
	}
	return (0);
}

int	get_cd(t_mini *mini, int i)
{
	char	*home_dir;

	home_dir = get_env("HOME", mini);
	if ((!mini->args[i + 1]))
	{
		change_dir(home_dir, mini);
		update_pwd(mini);
		return (1);
	}
	else
	{
		if (is_a_pipe(mini->args[i + 1], 0) || is_a_red(mini->args[i + 1])
			|| is_a_append_here(mini->args[i + 1]))
			return (1);
		if (has_two_args(mini->args, mini))
			return (1);
	}
	return (0);
}

int	ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}
