/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:17:31 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/17 13:45:22 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_char(char c, char *find)
{
	int	i;

	i = -1;
	while (find[++i])
		if (find[i] == c)
			return (1);
	return (0);
}

int	quotes_open(char *str, int target_index)
{
	int		open;
	char	wanted_quote;
	int		i;

	open = 0;
	i = 0;
	wanted_quote = -1;
	while (str[i])
	{
		if (find_char(str[i], "\"\'") && !open)
		{
			open = 1;
			wanted_quote = str[i++];
		}
		if (str[i] && open && str[i] == wanted_quote)
			open = 0;
		if (i == target_index)
			return (open);
		i++;
	}
	return (0);
}

int	pipe_check(t_mini *mini, char *str)
{
	int	i;

	i = -1;
	while (mini->args[++i])
	{
		if (!ft_strcmp(mini->args[i], "|") && !quotes_open(str, i))
		{
			if (i == 0)
			{
				ft_fprintf(2, "Minishell: syntax error");
				ft_fprintf(2, " near unexpected token `|'\n");
				return (0);
			}
			if (!mini->args[i + 1])
			{
				ft_fprintf(2, "Minishell: syntax error");
				ft_fprintf(2, " near unexpected token `|'\n");
				return (0);
			}
		}
	}
	return (1);
}

int	redirect_basic_check(char *str)
{
	int	i;
	int	count;

	i = -1;
	while (str[++i])
	{
		count = 0;
		if (find_char(str[i], "><") && !quotes_open(str, i))
		{
			while (str[i] && find_char(str[i], "><"))
			{
				if (find_char(str[i + 1], "><") && str[i + 1] != str[i])
					return (0);
				count++;
				i++;
			}
		}
		if (count > 2)
			return (0);
	}
	return (1);
}

int	remove_str(t_mini *mini, int i)
{
	char	**newvar;

	if (mini->args[i])
	{
		newvar = remove_var(mini->args, mini->args[i]);
		ft_free_arr(mini->args);
		mini->args = get_newenvp(newvar);
		ft_free_arr(newvar);
	}
	return (1);
}
