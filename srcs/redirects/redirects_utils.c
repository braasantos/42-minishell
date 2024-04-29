/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:30:10 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:03:31 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pipe(char **str, int i)
{
	if (!ft_strcmp(str[i], "|"))
	{
		if (!str[i + 1])
			return (print_error(2, str[i]), 1);
	}
	if (str[i + 1])
	{
		if (!ft_strcmp(str[i + 1], ">"))
		{
			if (str[i + 2])
			{
				if (create_and_exit(str[i + 2]))
					return (0);
			}
			else
				return (print_error(2, str[i]), 1);
		}
		if (check_options(str[i + 1]))
			return (print_error(1, str[i]), 1);
	}
	else
		return (print_error(1, str[i]), 1);
	return (0);
}

int	check_heredoc(char **str, int i)
{
	if (!ft_strcmp(str[i], ">>"))
	{
		if (str[i + 1])
		{
			if (check_options(str[i + 1]))
				return (print_error(1, str[i + 1]), 1);
			if (red_append(str, (i + 1)))
				return (print_error(3, str[i]), 1);
		}
		else
			return (print_error(2, str[i]), 1);
	}
	else
	{
		if (str[i + 1])
		{
			if (check_options(str[i + 1]))
				return (print_error(1, str[i + 1]), 1);
		}
		else
			return (print_error(2, str[i]), 1);
	}
	return (0);
}

int	handle_heredoc(char *s, t_mini *mini)
{
	if (check_options(s))
		return (print_error(1, s), 1);
	if (handle_heredoc2(s, mini))
		return (1);
	return (0);
}

int	heredoc_first(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], "<<"))
		{
			if (mini->args[i + 1])
			{
				if (handle_heredoc(mini->args[i + 1], mini))
					return (1);
			}
			else
			{
				print_error(2, mini->args[i]);
				return (1);
			}
		}
		i++;
	}
	if (!ft_strcmp(mini->args[0], "<<"))
		return (1);
	return (0);
}

int	handle_append(char *s)
{
	int		file;
	char	*str;

	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (is_a_file(str))
	{
		if (access(str, W_OK) == -1)
			return (free(str), 1);
	}
	file = open(s, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file == -1)
	{
		g_signal = 1;
		ft_fprintf(2, "Minishell: no file specified in redirect '>>'.\n");
		return (free(str), 1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (free(str), 0);
}
