/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:27:03 by bjorge-m          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/17 11:06:12 by braasantos       ###   ########.fr       */
=======
/*   Updated: 2024/04/17 17:09:56 by bjorge-m         ###   ########.fr       */
>>>>>>> refs/remotes/origin/master
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

static void	init_all(t_mini *mini)
{
	g_signal = 0;
	mini->newenvp = NULL;
	mini->another_split = NULL;
	mini->path_to_cmd = NULL;
	mini->exec_args = NULL;
	mini->args = NULL;
	mini->new_str = NULL;
	mini->before = NULL;
	mini->after = NULL;
	mini->echo_split = NULL;
	mini->fd1 = 0;
	mini->fd0 = 0;
	mini->stdin_fd = 0;
	mini->stdout_fd = 1;
	mini->exit_flag = 0;
	mini->echo_flag = 0;
	mini->flag_echo = 0;
	mini->free_flag = 0;
	mini->st_din = 0;
	mini->st_dout = 1;
	mini->pwd = NULL;
}

int	main(int ac, char **av)
{
	t_mini		mini;
	extern char	**environ;

	if (ac >= 2 && av)
		return (ft_putstr_fd("pls do not use arguments :(\n", 2), 0);
	init_all(&mini);
	mini.newenvp = get_newenvp(environ);
	do_shlvl(&mini);
	parser(&mini);
}

void	parser(t_mini *mini)
{
	while (1)
	{
		signals(1, mini);
		mini->str = readline("\001\033[0;34m\002minishell \001\033[0m\002");
		if (!mini->str)
			signals(3, mini);
		mini->new_str = pad_central(mini->str);
		mini->args = new_split(mini->new_str);
		// while_loop(mini->args);
		if (!mini->args[0])
		{
			free_struct(mini);
			continue ;
		}
		update_pwd(mini);
		check_comand(mini);
		add_history(mini->str);
		parsing(mini, mini->new_str);
		free_struct(mini);
	}
}