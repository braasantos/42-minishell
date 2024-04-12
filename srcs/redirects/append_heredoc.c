/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:56 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/12 18:35:23 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_red(t_mini *mini, char *s, char *ss)
{
	if (!ft_strcmp(s, ">>"))
		if (handle_append(ss))
			return (1);
	if (!ft_strcmp(s, "<<"))
		if (handle_heredoc(mini, ss))
			return (1);
	return (0);
}

int	handle_append(char *s)
{
	int	file;

	if (s)
	{
		file = open(s, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (file_ok(s, 1))
			return (1);
		if (!file)
		{
			ft_putstr_fd("Minishell: no file specified in redirect '>>'.\n", 2);
			return (1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	else
		return (1);
	return (0);
}

int	handle_heredoc(t_mini *mini, char *s)
{
	if (handle_heredoc2(s))
	{
		unlink(".heredoc");
		return (1);
	}
	mini->stdin_fd = open(".heredoc", O_RDONLY);
	if (mini->stdin_fd < 0)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '<<'.\n", 2);
		unlink(".heredoc");
		return (1);
	}
	return (0);
}

int	handle_heredoc2(char *delimiter)
{
	int		file;
	char	*input;

	file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (file < 0)
	{
		ft_putstr_fd("Minishell: could not open .heredoc file\n", 2);
		return (1);
	}
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (ft_putstr_fd("Minishell: heredoc interrupted\n", 2), 1);
		if (!ft_strcmp(input, delimiter))
			break ;
		ft_putstr_fd(input, file);
		ft_putchar_fd('\n', file);
		free(input);
	}
	free(input);
	close(file);
	return (0);
}
