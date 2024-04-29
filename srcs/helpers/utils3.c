/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:04:16 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:04:19 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_done(char **str, int i)
{
	if (!ft_strcmp(str[i], ">") || !ft_strcmp(str[i], ">>"))
	{
		if (!ft_strcmp(str[0], ">") || !ft_strcmp(str[0], ">>"))
		{
			if (str[i + 1])
			{
				if (!check_options(str[i + 1]))
				{
					if (create_and_exit(str[i + 1]))
						return (2);
				}
			}
		}
		if (str[i + 1])
		{
			if (check_options(str[i + 1]))
				return (print_error(1, str[i]), 2);
		}
		else
			return (print_error(2, str[i]), 2);
	}
	return (0);
}

int	exit_check(t_mini *mini, int i)
{
	char	**s;

	s = NULL;
	if (s)
	{
		ft_free_arr(s);
		s = NULL;
	}
	s = forming_echo_args(mini->args, i);
	if (arr_len(s) == 2)
	{
		if (!check_exit_arguments(s))
			return (0);
	}
	else if (arr_len(s) > 2)
	{
		g_signal = 1;
		ft_fprintf(2, "Minishell: %s: too many arguments\n", s[i]);
		if (ft_arrayisnum(mini->args))
			return (ft_free_arr(s), 0);
		else
			return (ft_free_arr(s), 1);
	}
	return (ft_free_arr(s), 0);
}

int	create_and_exit(char *str)
{
	int		file_fd;
	char	*s;

	if (count_quotes(str))
		s = ft_remove_quotes(str);
	else
		s = ft_strdup(str);
	file_fd = 0;
	if (is_a_file(str))
	{
		if (access(s, W_OK) == -1)
		{
			print_error(3, s);
			return (free(s), 1);
		}
	}
	file_fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file_fd == -1)
	{
		g_signal = 1;
		ft_fprintf(2, "Minishell: no file specified in redirect '>'.\n");
		return (free(s), 1);
	}
	close(file_fd);
	return (free(s), 1);
}
