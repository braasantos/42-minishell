/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:53 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:31:05 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_in_doc(int pipe_fd[2], char *delimiter, t_mini *mini)
{
	int		status;
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, mini->new_delimiter))
		{
			free(line);
			break ;
		}
		if (bingo(line, '$') && ft_strlen(line) > 1 && !count_quotes(delimiter))
			expand_str_hredoc(mini, &line);
		status = write(pipe_fd[1], line, ft_strlen(line));
		status = write(pipe_fd[1], "\n", 1);
		if (status == -1)
			ft_fprintf(2, "Minishell: Error writing to pipe\n");
		free(line);
	}
}

void	exit_heredoc(t_mini *mini)
{
	free(mini->pwd);
	free(mini->new_delimiter);
	mini->new_delimiter = NULL;
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->envp)
		ft_free_arr(mini->envp);
	exit(g_signal);
}

void	ft_manage_heredoc(int pipe_fd[2], char *delimiter, t_mini *mini)
{
	pid_t	pid;

	return_new_delimiter(delimiter, mini);
	return_mini(mini);
	pid = fork();
	ft_ignore_signals();
	if (pid == 0)
	{
		ft_doc_signals();
		ft_in_doc(pipe_fd, delimiter, mini);
		exit_heredoc(mini);
	}
	else
		waitpid(pid, &g_signal, 0);
	if (g_signal != 65280)
		dup2(pipe_fd[0], 0);
}

int	handle_heredoc2(char *delimiter, t_mini *mini)
{
	int	pipe_fd[2];
	int	i;

	i = pipe(pipe_fd);
	if (i == -1)
		return (ft_fprintf(2, "Minishell: Error creating pipe\n"), 1);
	redirect(mini);
	ft_manage_heredoc(pipe_fd, delimiter, mini);
	free(mini->new_delimiter);
	mini->new_delimiter = NULL;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}

char	*expand_str_hredoc(t_mini *mini, char **str)
{
	char	*s;
	char	*env;
	char	*ret;

	ret = ft_strdup("\0");
	free_expand2_heredoc(mini, 1, *str);
	if (bingo(*str, '?') && qmark_and_dollar(*str))
		get_qmark_heredoc(mini, str);
	free_expand2_heredoc(mini, 0, *str);
	while (bingo(*str, '$') && !quote_after_exp_hereodc(*str))
	{
		free_expand2_heredoc(mini, 1, *str);
		s = get_expand(*str);
		if (exit_expand_heredoc(s, mini))
			return (free(ret), NULL);
		env = get_env(s, mini);
		free(s);
		if (env)
			do_all_heredoc(mini, env, str);
		else
			return (free_expand2_heredoc(mini, 0, *str),
				*str = ft_strdup(ret), free(ret), NULL);
		free_expand2_heredoc(mini, 0, *str);
	}
	return (free(ret), env);
}
