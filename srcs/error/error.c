/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:25:50 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:25:52 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(int flag, char *s)
{
	if (flag == 1)
		ft_fprintf(2, "Mishell: syntax error near unexpected token `%s'\n", s);
	if (flag == 2)
	{
		ft_fprintf(2, "Mishell: syntax error ");
		ft_fprintf(2, "near unexpected token `newline'\n");
	}
	if (flag == 3)
	{
		ft_fprintf(2, "Mishell: Permission denied\n");
		g_signal = 1;
	}
}

void	print_cmd(t_mini *mini, int i)
{
	struct stat	stats;

	stat(mini->args[i], &stats);
	if (ft_strchr(mini->args[i], '/') && stat(mini->args[i], &stats))
		print(NO_SUCH_FILE_OR_DIR, mini->args[i]);
	else if (access(mini->args[i], F_OK))
		print(COMMAND_NOT_FOUND, mini->args[i]);
	else if (access(mini->args[i], F_OK | X_OK)
		&& ft_strchr(mini->args[i], '/'))
		print(NO_PERMISSION, mini->args[i]);
	else if (S_ISDIR(stats.st_mode))
		print(COMMAND_NOT_FOUND, mini->args[i]);
	else if (is_a_cmd(mini->args[i], mini) == false
		&& is_a_builtin(mini, i) == false)
		print(COMMAND_NOT_FOUND, mini->args[i]);
}

int	print(t_op op, char *ag)
{
	if (op == COMMAND_NOT_FOUND)
	{
		g_signal = 127;
		ft_putstr_fd(ag, 2);
		ft_fprintf(2, ": command not found\n");
	}
	else if (op == NO_SUCH_FILE_OR_DIR)
	{
		g_signal = 127;
		ft_putstr_fd(ag, 2);
		ft_fprintf(2, ": No such file or directory\n");
	}
	else if (op == NO_PERMISSION)
	{
		g_signal = 126;
		ft_putstr_fd(ag, 2);
		ft_fprintf(2, ": Permission denied\n");
	}
	else if (op == IS_DIR)
	{
		g_signal = 127;
		ft_putstr_fd(ag, 2);
		ft_fprintf(2, ": Is a directory\n");
	}
	return (1);
}
