/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:08:19 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 14:08:55 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirect(t_mini *mini)
{
	dup2(mini->stdin_fd, STDIN_FILENO);
	dup2(mini->stdout_fd, STDOUT_FILENO);
}

int	file_ok(char *s, int flag)
{
	int	fd;

	fd = 0;
	if (flag == 1)
	{
		if (access(s, W_OK) == -1)
			return (ft_putendl_fd(" Permission denied", 2), 1);
		fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd == -1)
		{
			close(fd);
			return (ft_putendl_fd(" No such file or directory", 2), 1);
		}
	}
	if (flag == 2)
	{
		fd = open(s, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			return (ft_putendl_fd(" No such file or directory", 2), 1);
		}
	}
	close(fd);
	return (0);
}
