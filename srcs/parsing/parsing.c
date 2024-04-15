/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:22:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/15 13:42:25 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_fork(t_mini *mini)
{
	if (mini->echo_split)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
	}
	mini->exit_flag = 1;
	unlink(".heredoc");
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	free(mini->newpro);
	exit(g_signal);
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
	char	*str;

	str = get_env("PWD", mini);
	if (!str)
		return (0);
	if (!ft_strcmp(s, str))
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
		{
			ft_free_arr(str);
			return (1);
		}
		if (!ft_strcmp(str[i], "1801"))
			remove_str(mini, i);
		i++;
	}
	ft_free_arr(str);
	return (0);
}

int	count_files(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_a_file(s[i]))
			count++;
		i++;
	}
	return (count);
}

int	command(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "grep"))
		return (1);
	if (!ft_strcmp(mini->args[0], "cat"))
		return (1);
	return (0);
}

int	doredirect(t_mini *mini)
{
	char	**str;

	if (count_files(mini->args) > 1 && command(mini))
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

int parsing(t_mini *mini, char *str)
{
	if (!ft_check_open_quotes(str))
		return (1);
	if (!redirect_basic_check(str))
	{
		ft_putendl_fd(" syntax error near unexpected token `>'", 2);
		return (1);
	}
	if (!pipe_check(mini, str))
		return (1);
	if (nAAAAAAAAAAAA(mini))
	{
		ft_putendl_fd(" Is a directory", 2);
		return (0);
	}
	if (!mini->args[0])
		return (2);
	if (doredirect(mini))
		return (1);
	if (execute(mini))
		return (1);
	return (0);
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
