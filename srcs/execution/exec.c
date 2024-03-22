/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:05:13 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/22 14:33:31 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute(t_mini *mini)
{
	int	n_pipes;

	n_pipes = count_pipes(mini);
	if (check_parser(mini) == 1)
		return ;
	if (check_here(mini) == 1)
		return ;
	if ((n_pipes == 0))
	{
		if (basic_builtin(mini))
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
		if (check_next(mini, i))
			break ;
		if (is_not_a_cmd(mini->args[i]))
		{
			if (create_child(mini, i, 1, j) == 1)
				break ;
			j++;
		}
		if (!ft_strcmp(mini->args[i], "echo"))
			while (mini->args[i] && check_options(mini->args[i]) == false)
				i++;
		if (!ft_strcmp(mini->args[i], "grep"))
			i++;
		if (mini->args[i])
			i++;
	}
	twenty_six_lines(mini);
}

int	create_child(t_mini *mini, int i, int flag, int j)
{
	ft_exit_builtin(mini, i);
	if (is_a_builtin(mini, i) == false)
		update_path(mini, i);
	mini->newpro[j] = fork();
	if (!mini->newpro[j])
	{
		hanlde_redirects(mini);
		if (flag == 1)
			through_pipes(mini, j);
		if (builtins(mini, i))
			exit(0);
		redirect(mini);
		if (is_a_builtin(mini, i) == false)
			handle_execve(mini, i);
	}
	if (mini->exit_flag != 1 && flag == 0)
		get_exit_status(mini);
	if (is_a_builtin(mini, i) == false)
		delete_path(mini);
	return (0);
}
