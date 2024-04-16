/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:22:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 17:10:35 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_fork(t_mini *mini)
{
	if (mini->echo_split)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
	}
	unlink(".heredoc");
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	free(mini->newpro);
	exit(g_signal);
}

int	bingo(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

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

int	remove_str(t_mini *mini, int i)
{
	char	**newvar;

	if (mini->args[i])
	{
		newvar = remove_var(mini->args, mini->args[i]);
		ft_free_arr(mini->args);
		mini->args = get_newenvp(newvar);
		ft_free_arr(newvar);
	}
	return (1);
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
		{
			ft_free_arr(str);
			return (1);
		}
		if (!ft_strcmp(str[i], "1801"))
			remove_str(mini, i);
		i++;
	}
	ft_free_arr(str);
	return (0);
}


int ft_define_error(t_mini *mini)
{
	struct stat path_stat;

	if (!strncmp(mini->args[0], "./", 2) || !strncmp(mini->args[0], "/", 1))
	{
		if (stat(mini->args[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				g_signal = 126;
				return ( ft_putendl_fd(" Is a directory", 2), 1);
			}
			else
			{
				if (access(mini->args[0], X_OK | R_OK | W_OK) == -1)
				{
					g_signal = 126;
					return (ft_putendl_fd(" Permission denied", 2), 1);
				}
			}
		}
		else
		{
			g_signal = 127;
			return ( ft_putendl_fd(" No such file or directory", 2), 1);
		}
	}
	return (0);
}
