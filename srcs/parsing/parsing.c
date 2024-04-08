/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:22:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/08 19:50:03 by braasantos       ###   ########.fr       */
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

int	nAAAAAAAAAAAA(t_mini *mini)
{
	int		i ;
	char	**str;

	i = 0;
	str = get_newenvp(mini->args);
	while (str[i])
	{
		if (check_pwd(str[0], mini))
			return (1);
		if (!ft_strcmp(str[i], "1801"))
			remove_str(mini, i);
		i++;
	}
	return (0);
}

int	doredirect(t_mini *mini)
{
	char	**str;

	if (!ft_strcmp(mini->args[0], "echo"))
		return (0);
	if (have_redirect(mini))
	{
		str = echo_w_red(mini->args);
		if (!str)
			return (1);
		ft_free_arr(mini->args);
		mini->args = get_newenvp(str);
		ft_free_arr(str);
	}
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
	if (!mini->args[0])
		return ;
	// if (doredirect(mini))
	// 	return ;
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
