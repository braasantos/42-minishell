/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:56 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/30 15:31:35 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_red(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], ">>"))
		if (handle_append(mini, i))
			return (1);
	if (!ft_strcmp(mini->args[i], "<<"))
		if (handle_heredoc(mini, i))
			return (1);
	return (0);
}

int	handle_append(t_mini *mini, int i)
{
	int	file;

	if (mini->args[i + 1])
	{
		if (file_ok(mini->args[i + 1], 1))
			return (1);
		file = open(mini->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
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

int	handle_heredoc(t_mini *mini, int i)
{
	if (handle_heredoc2(mini->args[i + 1]))
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
