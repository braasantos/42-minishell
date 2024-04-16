/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:24:39 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 16:20:44 by bjorge-m         ###   ########.fr       */
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
			|| !ft_strcmp(mini->args[i], ">>"))
			count++;
		i++;
	}
	return (count);
}

int	redirect_output(char *s, t_mini *mini)
{
	int		file_fd;
	char	*str;

	(void)mini;
	if (!s)
		return (1);
	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	file_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file_ok(str, 1))
		return (free(str), 1);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (free(str), 1);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (free(str), 0);
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

int	more_red(t_mini *mini, int i)
{
	int	count;

	count = 0;
	while (mini->args[++i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
		{
			redirect_output(mini->args[i + 1], mini);
			count++;
		}
		if (!ft_strcmp(mini->args[i], "<"))
		{
			redirect_output(mini->args[i + 1], mini);
			count++;
		}
	}
	return (count);
}

int	hanlde_redirects(t_mini *mini, char **s, int i, int flag)
{
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">"))
		{
			if (redirect_output(s[i + 1], mini))
				return (g_signal = 1);
		}
		if (!ft_strcmp(mini->args[i], "<"))
		{
			if (redirect_input(s[i + 1]))
				return (g_signal = 1);
		}
		if (handle_red(mini, s[i], s[i + 1], flag))
			return (g_signal = 1);
		i++;
	}
	return (0);
}
