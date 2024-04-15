/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:54:16 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/15 17:21:38 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_arg(char *str, int current, int flag, char **args)
{
	int	i;
	int	total;

	i = 0;
	total = str_len(args);
	while (str[i])
	{
		if (ft_strstartswith(str, "\"") || ft_strendswith(str, "\""))
		{
			if (str[i] != '\"')
				write(1, &str[i], 1);
		}
		else if (ft_strstartswith(str, "\'") || ft_strendswith(str, "\'"))
		{
			if (str[i] != '\'')
				write(1, &str[i], 1);
		}
		else
			if (str[i] != '\"' && str[i] != '\'')
				write(1, &str[i], 1);
		i++;
	}
	if (flag == 0)
		if (total - 1 > current)
			write(1, " ", 1);
}

int	check_pos_str(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">"))
			return (i);
		if (!ft_strcmp(s[i], "<"))
			return (i);
		if (!ft_strcmp(s[i], ">>"))
			return (i);
		if (!ft_strcmp(s[i], "<<"))
			return (i);
		i++;
	}
	return (0);
}

void	check_echo(t_mini *mini)
{
	char	**s;
	int		pos_red;
	int		pos_file;

	s = NULL;
	while (have_redi(mini->echo_split))
	{
		pos_red = check_pos_str(mini->echo_split);
		pos_file = pos_red + 1;
		s = new_args(mini->echo_split, pos_red, pos_file);
		if (mini->echo_split)
		{
			ft_free_arr(mini->echo_split);
		}
		mini->echo_split = get_newenvp(s);
		ft_free_arr(s);
	}
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
			print_arg(tokens[i], i, mini->echo_flag, tokens);
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
