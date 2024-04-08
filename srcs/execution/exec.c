/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:05:13 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/08 17:49:42 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtins_check(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
	{
		free_struct_2(mini);
		return (1);
	}
	if (!ft_strcmp(mini->args[i], "pwd"))
		return (print_pwd(mini, i));
	if ((!ft_strcmp(mini->args[i], "cd")))
		return (get_cd(mini, i));
	if ((!ft_strcmp(mini->args[i], "env")))
		return (get_envp(mini));
	if ((!ft_strcmp(mini->args[i], "export")))
	{
		if (check_env(mini))
			return (1);
		return (get_export(mini));
	}
	if ((!ft_strcmp(mini->args[i], "unset")))
	{
		if (check_env(mini))
			return (1);
		return (get_unset(mini));
	}
	return (0);
}

void	execute(t_mini *mini)
{
	int	n_pipes;

	n_pipes = count_pipes(mini);
	if (check_parser(mini) == 1)
		return ;
	if (check_here(mini) == 1)
		return ;
	if (n_pipes == 0)
	{
		if (builtins_check(mini, 0))
			return ;
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_child(mini, 0, 0, 0);
		free(mini->newpro);
	}
	else if ((n_pipes > 0))
	{
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_flow(mini);
		free(mini->newpro);
	}
}

int	pipe_creation(t_mini *mini)
{
	int	i;
	int	n_pipes;

	n_pipes = count_pipes(mini);
	mini->pipes_fd = malloc(sizeof(int) * (n_pipes * 2));
	i = 0;
	while (i < n_pipes)
	{
		if (pipe(mini->pipes_fd + (2 * i)) < 0)
		{
			ft_putstr_fd("Error while creating pipes", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

bool is_not_a_cmd(char *s)
{
	if (is_a_pipe(s) || is_a_red(s) || ft_strstartswith(s, "-") || count_quotes(s) > 0 || is_a_append_here(s) || is_a_file(s) || is_a_number(s))
		return (false);
	return (true);
}

void create_flow(t_mini *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	pipe_creation(mini);
	while (mini->args[i])
	{
		if (is_not_a_cmd(mini->args[i]))
		{
			if (create_child(mini, i, 1, j) == 1)
				break ;
			j++;
		}
		if (is_not_a_cmd(mini->args[i]))
			while (mini->args[i] && ft_strcmp(mini->args[i], "|"))
				i++;
		if (mini->args[i])
			i++;
	}
	twenty_six_lines(mini);
}

int	create_child(t_mini *mini, int i, int flag, int j)
{
	mini->exit_flag = 0;
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		update_path(mini, i);
	if (null_args(mini, i))
		return (0);
	mini->newpro[j] = fork();
	if (!mini->newpro[j])
	{
		if (ft_strcmp(mini->args[i], "echo"))
			if (hanlde_redirects(mini, mini->args))
				exit_fork(mini);
		through_pipes(mini, j, flag);
		if (builtins(mini, i))
			exit_fork(mini);
		redirect(mini);
		handle_execve(mini, i);
	}
	if (mini->exit_flag != 1 && flag == 0)
		get_exit_status(mini);
	if (is_a_builtin(mini, i) == false && is_a_cmd(mini->args[i], mini))
		delete_path(mini);
	return (0);
}
