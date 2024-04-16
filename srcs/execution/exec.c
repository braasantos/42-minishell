/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:05:13 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 14:40:55 by gabe             ###   ########.fr       */
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
		return (print_pwd(mini));
	if ((!ft_strcmp(mini->args[i], "cd")))
		return (get_cd(mini, i));
	if ((!ft_strcmp(mini->args[i], "env")))
		return (get_envp(mini));
	if ((!ft_strcmp(mini->args[i], "export"))
		|| (!ft_strcmp(mini->args[i], "unset")))
		if (check_env(mini))
			return (1);
	if ((!ft_strcmp(mini->args[i], "export")))
		return (get_export(mini));
	if ((!ft_strcmp(mini->args[i], "unset")))
		return (get_unset(mini));
	if (!ft_strcmp(mini->args[i], "grep"))
	{
		if (get_grep(mini, i))
			return (1);
	}
	return (0);
}

int	execute(t_mini *mini)
{
	int	n_pipes;

	n_pipes = count_pipes(mini);
	if (n_pipes == 0)
	{
		if (check_parser(mini) == 1 || check_here(mini) == 1)
			return (1);
		if (builtins_check(mini, 0))
			return (0);
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_child(mini, 0, 0, 0);
		free(mini->newpro);
	}
	else if ((n_pipes > 0))
	{
		if (check_parser_full(mini) == 1)
			return (1);
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_flow(mini);
		free(mini->newpro);
	}
	return (0);
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

bool	is_not_a_cmd(char *s)
{
	if (is_a_pipe(s) || is_a_red(s) || ft_strstartswith(s, "-")
		|| count_quotes(s) > 0 || is_a_append_here(s)
		|| is_a_file(s) || is_a_number(s))
		return (false);
	return (true);
}

void	create_flow(t_mini *mini)
{
	int	i;
	int	j;

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
