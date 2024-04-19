/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:56 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/19 16:31:14 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_red(t_mini *mini, char *s, char *ss, int flag)
{
	(void)flag;
	(void)mini;
	if (!ft_strcmp(s, ">>"))
		if (handle_append(ss))
			return (1);
	return (0);
}

int	handle_append(char *s)
{
	int	file;

	if (s)
	{
		file = open(s, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (file_ok(s, 2))
		{
			g_signal = 1;
			return (1);
		}
		if (!file)
		{
			g_signal = 1;
			ft_fprintf(2, "Minishell: no file specified in redirect '>>'.\n");
			return (1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	else
	{
		g_signal = 1;
		return (1);
	}
	return (0);
}

int	handle_heredoc(t_mini *mini, char *s)
{
	if (check_options(s))
		return (ft_fprintf(1, "syntax error near unexpected token `newline'\n"));
	if (handle_heredoc2(s, mini))
	{
		unlink(".heredoc");
		return (1);
	}
	return (0);
}

int	handle_heredoc2(char *delimiter, t_mini *mini)
{
	int		file;
	char	*input;
	pid_t	forq;

	file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (file < 0)
	{
		ft_fprintf(2, "Minishell: could not open .heredoc file\n");
		return (1);
	}
	forq = fork();
	if (forq == 0)
	{
		// ft_doc_signals();
		while (1)
		{
			input = readline("> ");
			if (!input)
				return (ft_fprintf(2, "Minishell: heredoc interrupted\n"), 1);
			if (!ft_strcmp(input, delimiter))
				exit_fork_here_doc(mini);
			ft_putstr_fd(input, file);
			ft_putchar_fd('\n', file);
			free(input);
		}
		free(input);
	}
	close(file);
	wait(&forq);
	return (0);
}

void	redirect(t_mini *mini)
{
	dup2(mini->stdin_fd, STDIN_FILENO);
	dup2(mini->stdout_fd, STDOUT_FILENO);
}
