/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:22:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/29 17:24:12 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_exit(t_mini *mini, int i)
{
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		delete_path(mini);
	if (mini->echo_flag == 1)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_flag = 0;
	}
	ft_free_arr(mini->args);
	free(mini->new_str);
	free(mini->str);
	free(mini->newpro);
	ft_free_arr(mini->newenvp);
	exit(1);
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

int nAAAAAAAAAAAA(t_mini *mini)
{
	char **s;
	char *c;
	int i;

	s = NULL;
	i = 0;
	c = get_env("PWD", mini);
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[0], c))
		{
			ft_printf("Minishell: %s Is a directory\n", mini->args[i]);
			return (1);
		}
		if (!ft_strcmp(mini->args[i], "1801"))
		{
			s = remove_var(mini->args, mini->args[i]);
			ft_free_arr(mini->args);
			mini->args = get_newenvp(s);
			ft_free_arr(s);
		}
		i++;
	}
	return (0);
}

void parsing(t_mini *mini, char *str)
{
	if (!ft_check_open_quotes(str))
		return;
	if (!redirect_basic_check(str))
		ft_printf("invalid redirect\n");
	if (!pipe_check(mini, str))
		return;
	if (nAAAAAAAAAAAA(mini))
		return;
	if (handle_split_args(mini))
		return;
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
