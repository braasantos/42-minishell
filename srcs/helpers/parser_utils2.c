/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:54 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:26:55 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_n(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], " "))
			count++;
		i++;
	}
	return (count);
}

int	change_args(t_mini *mini, char ***args)
{
	char	**s;
	int		len;

	(void)mini;
	s = NULL;
	len = count_n(*args);
	if (len > 0)
	{
		s = check_empty(*args);
		if (!s)
		{
			ft_free_arr(s);
			return (1);
		}
		ft_free_arr(*args);
		*args = ft_arrcpy(s);
		ft_free_arr(s);
	}
	g_signal = 0;
	return (0);
}

int	count_not_n(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], " "))
			count++;
		i++;
	}
	return (count);
}

char	**check_empty(char **args)
{
	int		i;
	char	**s;
	int		len;
	int		j;

	s = NULL;
	j = 0;
	i = 0;
	len = count_not_n(args);
	if (len > 0)
	{
		s = ft_calloc(sizeof(char *), len + 1);
		while (args[i])
		{
			if (ft_strcmp(args[i], " "))
			{
				s[j] = ft_strdup(args[i]);
				j++;
			}
			i++;
		}
		s[j] = NULL;
		return (s);
	}
	return (s);
}

int	remove_str(char ***str, int i)
{
	char	**newvar;

	newvar = NULL;
	if ((*str)[i])
	{
		newvar = remove_var(*str, (*str)[i]);
		ft_free_arr(*str);
		*str = newvar;
	}
	return (1);
}
