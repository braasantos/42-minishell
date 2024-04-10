/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:24:39 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/10 21:28:04 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_red(t_mini *mini)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "<") == 0
			|| ft_strcmp(mini->args[i], ">") == 0
			|| !ft_strcmp(mini->args[i], ">>")
			|| !ft_strcmp(mini->args[i], ">>"))
			count++;
		i++;
	}
	return (count);
}

int	redirect_output(char *s)
{
	int	file_fd;

	if (!s)
		return (1);
	file_fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file_ok(s, 1))
		return (1);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (1);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (0);
}

int	redirect_input(char *s)
{
	int	file_fd;

	file_fd = open(s, O_RDONLY);
	if (file_ok(s, 2))
		return (1);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '<'.\n", 2);
		return (1);
	}
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (0);
}

int	hanlde_redirects(t_mini *mini, char **s, int i)
{
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">"))
			if (redirect_output(s[i + 1]))
				return (1);
		if (!ft_strcmp(mini->args[i], "<"))
			if (redirect_input(s[i + 1]))
				return (1);
		if (handle_red(mini, s[i], s[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

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
