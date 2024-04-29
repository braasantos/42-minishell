/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:07:09 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:07:11 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

static void	init_struct(t_mini *mini)
{
	g_signal = 0;
	mini->envp = NULL;
	mini->args = NULL;
	mini->before = NULL;
	mini->after = NULL;
	mini->pwd = NULL;
	mini->echo_split = NULL;
	mini->stdin_fd = dup(STDIN_FILENO);
	mini->stdout_fd = dup(STDOUT_FILENO);
	mini->path_to_cmd = NULL;
	mini->exec_args = NULL;
	mini->new_delimiter = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	if (ac >= 2 && av)
		return (ft_fprintf(2, "DO NOT USE ANY ARGUMENTS\n"));
	init_struct(&mini);
	mini.envp = ft_arrcpy(envp);
	ft_init_signals();
	do_shlvl(&mini);
	parser(&mini);
}
