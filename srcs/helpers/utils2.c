/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:13:45 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/17 13:45:49 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_open_quotes(char *str)
{
	char	quote;
	int		state;

	state = 0;
	while (*str)
	{
		if (!state && (*str == '\'' || *str == '\"'))
		{
			state = 1;
			quote = *str;
		}
		else if (state && *str == quote)
			state = 0;
		str++;
	}
	if (state && write(2, "Error: Open quotes\n", 19))
	{
		g_signal = 2;
		return (0);
	}
	return (1);
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

int	check_args(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			j++;
		i++;
	}
	if (j >= 1)
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1[i] || !str2[i])
		return (1);
	while (str1[i] || str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}

int	str_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}