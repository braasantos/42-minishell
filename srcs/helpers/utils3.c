/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:14:00 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/19 16:11:47 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_parser(t_mini *mini)
{
	int	i;

	i = -1;
	while (mini->args[++i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
		{
			if (mini->args[i + 1])
			{
				if (check_parser2(mini, (i + 1)))
					break ;
			}
			else
			{
				ft_putendl_fd(STX_ERROR, 2);
				return (g_signal = 2, 1);
			}
		}
		if (!ft_strcmp(mini->args[i], "<"))
			if (check_parser3(mini, i))
				return (1);
		if (do_redirects(mini, i) == 1)
			return (g_signal = 1, 1);
	}
	return (0);
}

int	check_parser_full(t_mini *mini)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">") || !ft_strcmp(mini->args[i], ">>"))
		{
			if (!mini->args[i + 1])
				return (ft_fprintf(1, "Minishell: syntax error near unexpected token `newline'\n"), 1);
			if (mini->args[i + 1]  && !ft_strcmp(mini->args[i], ">"))
			{
				fd = open(mini->args[i + 1],
						O_WRONLY | O_CREAT | O_TRUNC, 0664);
			}
			if (access(mini->args[i + 1], W_OK | X_OK) == -1)
					break ;
		}
		if (!ft_strcmp(mini->args[i], "<"))
			is_a_file(mini->args[i + 1]);
		i++;
	}
	return (fd);
}

int	check_parser3(t_mini *mini, int i)
{
	if (mini->args[i + 1])
	{
		if (!ft_strcmp(mini->args[i + 1], ">"))
			return (0);
		if (is_a_file(mini->args[i + 1]))
			return (0);
		if (check_options(mini->args[i + 1]))
		{
			g_signal = 2;
			return (ft_fprintf(2, " syntax error near unexpected token \n"), 1);
		}
		else
		{
			g_signal = 1;
			ft_fprintf(2, " No such file or directory\n");
			return (1);
		}
	}
	else
	{
		g_signal = 2;
		ft_putendl_fd(STX_ERROR, 2);
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

bool	db_quotes(char *str)
{
	int	quotes;

	quotes = 0;
	while (*str)
		if (*str++ == '\"')
			quotes++;
	return (quotes);
}
