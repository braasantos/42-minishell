/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:54:16 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/21 12:56:37 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_arg(char *str, t_mini *mini, int current, int flag)
{
	int	i;
	int	total;

	i = 0;
	total = str_len(mini->echo_split);
	while (str[i])
	{
		if (str[i] != '"')
			write(1, &str[i], 1);
		i++;
	}
	if (flag == 0)
		if (total - 1 > current)
			write(1, " ", 1);
}

int	echo_cmd(char **tokens, t_mini *mini)
{
	int	flag_nl;
	int	option;
	int	i;

	i = 1;
	flag_nl = 1;
	option = 1;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "-n") && option)
		{
			flag_nl = 0;
			i++;
		}
		else
			option = 0;
		if (!option)
		{
			print_arg(tokens[i], mini, i, mini->echo_flag);
			i++;
		}
	}
	return (ft_print_new_line(flag_nl), 1);
}

void	ft_print_new_line(int flag_nl)
{
	if (flag_nl)
		ft_printf("\n");
}

int	redirect_output_echo(int i, t_mini *mini)
{
	int	file_fd;

	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
		{
			if (!mini->args[i + 1])
				return (1);
			file_fd = open(mini->args[i + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (!file_fd)
			{
				ft_putstr_fd("Minishell: no filespecified", 2);
				ft_putstr_fd("in redirect '>' . \n", 2);
				return (1);
			}
			dup2(file_fd, STDOUT_FILENO);
			close(file_fd);
		}
		if (!ft_strcmp(mini->args[i], ">>"))
			handle_append(mini, i);
		i++;
	}
	return (0);
}

bool	db_quotes(char *str)
{
	int	quotes;

	quotes = 0;
	while (*str)
		if (*str++ == '\"')
			quotes++;
	return (quotes);
}
