/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:14:00 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/02 15:48:12 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_parser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
		{
			if (mini->args[i + 1])
				return (check_parser2(mini, (i + 1)));
			else
			{
				ft_putstr_fd("minishell: syntax error ", 2);
				ft_putendl_fd("unexpected token `newline'", 2);
				return (1);
			}
		}
		if (!ft_strcmp(mini->args[i], "<"))
			return (check_parser3(mini, i));
		if (do_redirects(mini, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_parser3(t_mini *mini, int i)
{
	if (mini->args[i + 1])
	{
		if (!ft_strcmp(mini->args[i + 1], ">"))
			return (0);
		if (is_a_file(mini->args[i + 1]))
			return (0);
		else
		{
			ft_putstr_fd("Minishell: No such ", 2);
			ft_putstr_fd(mini->args[i + 1], 2);
			ft_putendl_fd(" file or directory", 2);
			return (1);
		}
	}
	else
	{
		ft_putendl_fd("Minishell: syntax error near unexpected token `newline'", 2);
		return (1);
	}
	return (0);
}

int	do_redirects(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "<<"))
	{
		if (mini->args[i + 1])
		{
			return (print_error(mini->args[i + 1]));
			return (0);
		}
		else
		{
			ft_putstr_fd("minishell: syntax error ", 2);
			ft_putendl_fd("near unexpected token `newline'", 2);
			return (1);
		}
	}
	if (!ft_strcmp(mini->args[i], ">>"))
	{
		if (mini->args[i + 1])
			return (0);
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putendl_fd("near unexpected token `newline'", 2);
		return (1);
	}
	return (0);
}

char	*ft_remove_quotes(char *str)
{
	char	*new;
	int		count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	count = count_quotes(str);
	i = ft_strlen(str) - count;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
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
