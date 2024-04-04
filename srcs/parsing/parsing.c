/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:22:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/04 18:03:58 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_fork(t_mini *mini)
{
	int		devnull;
	char	*argv[3];

	(void)mini;
	devnull = open("/dev/null", O_WRONLY);
	if (dup2(devnull, STDOUT_FILENO) == -1
		|| dup2(devnull, STDERR_FILENO) == -1)
	{
		close(devnull);
		exit(EXIT_FAILURE);
	}
	close(devnull);
	argv[0] = "/bin/echo";
	argv[1] = "Hello, World!";
	argv[2] = NULL;
	execve(argv[0], argv, NULL);
	exit(EXIT_FAILURE);
}

int bingo(char *s, char c)
{
	int i;

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
	if (!ft_strcmp(s, get_env("PWD", mini)))
	{
		g_signal = 126;
		return (1);
	}
	return (0);
}

char	*cut_lines(t_mini *mini, char *s, int i)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(s, " ");
	free(s);
	s = ft_strjoin(temp, mini->args[i]);
	free(temp);
	return (s);
}

int	nAAAAAAAAAAAA(t_mini *mini)
{
	int		i = 0;
	char	*ss;

	i = -1;
	ss = NULL;
	while (mini->args[++i])
	{
		if (check_pwd(mini->args[0], mini))
			return (1);
		if (ft_strcmp(mini->args[i], "1801"))
		{
			if (ss == NULL)
				ss = ft_strdup(mini->args[i]);
			else
				ss = cut_lines(mini, ss, i);
		}
	}
	ft_free_arr(mini->args);
	mini->args = ft_split(ss, ' ');
	free(ss);
	return (0);
}


void parsing(t_mini *mini, char *str)
{
	if (!ft_check_open_quotes(str))
		return ;
	if (!redirect_basic_check(str))
		ft_putendl_fd("invalid redirect", 2);
	if (!pipe_check(mini, str))
		return ;
	if (nAAAAAAAAAAAA(mini))
	{
		ft_putendl_fd(" Is a directory", 2);
		return ;
	}
	if (!mini->args)
		return ;
	execute(mini);
}

void sigint_on_child(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void get_exit_status(t_mini *mini)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (i < count_pipes(mini) + 1)
	{
		signal(SIGINT, &sigint_on_child);
		waitpid(mini->newpro[i], &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
		i++;
	}
}
