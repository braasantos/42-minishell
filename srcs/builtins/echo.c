/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:54:16 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/02 18:09:59 by bjorge-m         ###   ########.fr       */
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
	mini->echo_flag = 0;
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

bool	db_quotes(char *str)
{
	int	quotes;

	quotes = 0;
	while (*str)
		if (*str++ == '\"')
			quotes++;
	return (quotes);
}
