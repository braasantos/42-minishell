/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:17:19 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/17 13:46:48 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_squotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

void	while_loop(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_printf("%s\n", s[i]);
		i++;
	}
}

char	*ft_touppercase(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - ('a' - 'A');
		i++;
	}
	return (s);
}

int	print_error(char *s)
{
	if (!ft_strcmp(s, ">"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'", 2);
		return (1);
	}
	return (0);
}

int	check_next(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], ">")
		|| (!ft_strcmp(mini->args[i], "<"))
		|| is_a_append_here(mini->args[i]))
	{
		if (mini->args[i + 1])
			return (1);
	}
	return (0);
}
int	count_red_pipe(t_mini *mini)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
			count++;
		if (!ft_strcmp(mini->args[i], "<"))
			count++;
		if (!ft_strcmp(mini->args[i], ">>"))
			count++;
		if (!ft_strcmp(mini->args[i], "|"))
			count++;
		i++;
	}
	return (count);
}

int	im_done_parser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">") || !ft_strcmp(mini->args[i], "<"))
		{
			if (mini->args[i + 1])
			{
				if (check_options(mini->args[i + 1]))
				{
					g_signal = 2;
					ft_fprintf(2, " syntax error near unexpected token `%s'\n", mini->args[i + 1]);
					return (1);
				}
			}
			else
			{
				g_signal = 2;
				ft_fprintf(2, " syntax error near unexpected token `newline'\n");
				return (1);
			}

		}
		i++;
	}
	return (0);
}
