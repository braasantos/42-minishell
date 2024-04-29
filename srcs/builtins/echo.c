/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:23:06 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:23:07 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_cmd(char **tokens, t_mini *mini)
{
	int	flag_nl;
	int	option;
	int	i;

	i = 1;
	flag_nl = 1;
	option = 1;
	mini->echo_flag = 0;
	g_signal = 0;
	while (tokens[i])
	{
		if (check_flag(tokens[i]) && option)
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

int	check_flag(char *s)
{
	int		i;
	int		count;
	char	*str;

	i = 1;
	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	count = 0;
	if (str[0] == '-')
	{
		while (str[i] == 'n' && str[i])
		{
			count++;
			i++;
		}
		if (str[i] != 'n' && str[i])
			return (free(str), 0);
	}
	return (free(str), count);
}

void	print_arg(char *str, int current, int flag, char **args)
{
	int	i;
	int	total;

	i = 0;
	total = arr_len(args) - 1;
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
		if (total > current)
			write(1, " ", 1);
}

int	hanlde_redirects(t_mini *mini, char **s, int i)
{
	while (s[i])
	{
		if (!ft_strcmp(s[i], ">"))
		{
			if (redirect_output(s[i + 1]))
				return (g_signal = 1, 1);
		}
		if (!ft_strcmp(mini->args[i], "<"))
		{
			if (redirect_input(s[i + 1]))
				return (g_signal = 1, 1);
		}
		if (deal_append(s[i], s[i + 1]))
			return (g_signal = 1, 1);
		i++;
	}
	return (0);
}
