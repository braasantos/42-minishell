/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:56 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/29 17:30:10 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_red(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], ">>"))
		handle_append(mini, i);
	if (!ft_strcmp(mini->args[i], "<<"))
		handle_heredoc(mini, i);
}

void	handle_append(t_mini *mini, int i)
{
	int	file;

	if (mini->args[i + 1])
	{
		if (file_ok(mini->args[i + 1], 1))
			return ;
		file = open(mini->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (!file)
		{
			ft_putstr_fd("Minishell: no file specified in redirect '>>'.\n", 2);
			return ;
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	else
		return ;
}

void	handle_heredoc(t_mini *mini, int i)
{
	if (handle_heredoc2(mini->args[i + 1]))
	{
		free_child_p(mini);
		exit(2);
	}
	mini->stdin_fd = open(".heredoc", O_RDONLY);
	if (mini->stdin_fd < 0)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '<<'.\n", 2);
		free_child_p(mini);
		exit(2);
	}
}

int	free_child_p(t_mini *mini)
{
	unlink(".heredoc");
	free_struct(mini);
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
