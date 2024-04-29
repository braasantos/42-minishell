/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:30:06 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:01:45 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	red_append(char **s, int i)
{
	int		file_fd;
	char	*str;

	if (count_quotes(s[i]))
		str = ft_remove_quotes(s[i]);
	else
		str = ft_strdup(s[i]);
	file_fd = 0;
	if (is_a_file(str))
	{
		if (access(str, W_OK) == -1)
			return (free(str), 1);
	}
	file_fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file_fd == -1)
	{
		g_signal = 1;
		ft_fprintf(2, "Minishell: no file specified in redirect '>>'.\n");
		return (free(str), 1);
	}
	close(file_fd);
	return (free(str), 0);
}

static int	redirect_out(char **str, int i)
{
	int		file_fd;
	char	*s;

	if (count_quotes(str[i]))
		s = ft_remove_quotes(str[i]);
	else
		s = ft_strdup(str[i]);
	file_fd = 0;
	if (is_a_file(str[i]))
	{
		if (access(s, W_OK) == -1)
			return (free(s), 1);
	}
	file_fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file_fd == -1)
	{
		g_signal = 1;
		ft_fprintf(2, "Minishell: no file specified in redirect '>'.\n");
		return (free(s), 1);
	}
	close(file_fd);
	return (free(s), 0);
}

static int	redirect_in(char **str, int i)
{
	int		file_fd;
	char	*s;

	if (count_quotes(str[i]))
		s = ft_remove_quotes(str[i]);
	else
		s = ft_strdup(str[i]);
	file_fd = open(s, O_RDONLY);
	if (is_a_file(str[i]))
	{
		if (access(s, W_OK) == -1)
			return (free(s), print_error(3, str[i + 1]), 1);
	}
	if (file_fd == -1)
	{
		g_signal = 1;
		free(s);
		return (ft_fprintf(2, "Minishell: No such file or directory\n"), 1);
	}
	close(file_fd);
	return (free(s), 0);
}

static int	check_all_red_utils(char **str, int i, int flag)
{
	if (flag == 1)
	{
		if (str[i])
		{
			if (check_options(str[i]))
				return (print_error(1, str[i]), 1);
			if (redirect_out(str, i))
				return (print_error(3, str[i]), 1);
		}
		else
			return (print_error(2, str[i]), 1);
	}
	else
	{
		if (str[i])
		{
			if (check_options(str[i]))
				return (print_error(1, str[i]), 1);
			if (redirect_in(str, i))
				return (1);
		}
		else
			return (print_error(2, str[i]), 2);
	}
	return (0);
}

int	check_all_redirects(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (check_done(str, i) == 2)
			return (2);
		if (!ft_strcmp(str[i], ">"))
			if (check_all_red_utils(str, (i + 1), 1))
				return (1);
		if (!ft_strcmp(str[i], "<"))
		{
			if (check_all_red_utils(str, (i + 1), 0))
				return (1);
		}
		if (!ft_strcmp(str[i], "|"))
			if (check_pipe(str, i))
				return (2);
		if (!ft_strcmp(str[i], "<<") || !ft_strcmp(str[i], ">>"))
		{
			if (check_heredoc(str, i))
				return (1);
		}
	}
	return (0);
}
