/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:28 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:29:29 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_s_quotes(char **str, int i, char *s)
{
	int	d_quotes;
	int	s_quotes;

	d_quotes = count_dquote_pairs(str[i]);
	s_quotes = count_squote_pairs(str[i]);
	if (s_quotes >= 2)
	{
		if (s_quotes % 2 == 0)
		{
			s = ft_remove_squotes(str[i]);
			free(str[i]);
			str[i] = ft_strdup(s);
			free(s);
		}
	}
	else if ((d_quotes > 0 && s_quotes > 0))
	{
		if (s_quotes % 2 == 0)
		{
			s = ft_remove_squotes(str[i]);
			free(str[i]);
			str[i] = ft_strdup(s);
			free(s);
		}
	}
}

void	time_to_remove(char **str, int i)
{
	char	*s;

	s = NULL;
	if (ft_strstartswith(str[i], "\""))
		remove_d_quotes(str, i, s);
	if (ft_strstartswith(str[i], "\'"))
		remove_s_quotes(str, i, s);
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
