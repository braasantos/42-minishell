/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:22:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/19 16:42:46 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pwd(char *s, t_mini *mini)
{
	char	*str;

	str = get_env("PWD", mini);
	if (!str)
		return (0);
	if (!ft_strcmp(s, str))
	{
		g_signal = 126;
		return (1);
	}
	return (0);
}

int	check_empty(t_mini *mini)
{
	int		i ;
	char	**str;

	i = 0;
	str = get_newenvp(mini->args);
	while (str[i])
	{
		if (check_pwd(str[0], mini))
			return (ft_free_arr(str), 1);
		if (!ft_strcmp(str[i], "1801"))
			remove_str(mini, i);
		i++;
	}
	ft_free_arr(str);
	return (0);
}

void	definr_error_help(int flag)
{
	if (flag == 1)
	{
		g_signal = 126;
		ft_fprintf(2, " Is a directory\n");
	}
	else if (flag == 2)
	{
		g_signal = 126;
		ft_fprintf(2, " Permission denied\n");
	}
	else
	{
		g_signal = 127;
		ft_fprintf(2, " No such file or directory\n");
	}
}

int ft_define_error(t_mini *mini)
{
	struct stat path_stat;

	if (!strncmp(mini->args[0], "./", 2) || !strncmp(mini->args[0], "/", 1))
	{
		if (stat(mini->args[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
				return (definr_error_help(1), 1);
			else
			{
				if (access(mini->args[0], X_OK | R_OK | W_OK) == -1)
				return (definr_error_help(2), 1);
			}
		}
		else
			return (definr_error_help(3), 1);
	}
	return (0);
}
