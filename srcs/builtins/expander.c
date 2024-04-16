/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/16 18:49:13 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_expand(char *s)
{
	int		i;
	char	*str;
	int		len;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s) - 1;
	str = malloc(sizeof(char) * (len + 2));
	while (s[i] != '$')
		i++;
	while (s[i])
	{
		if (s[i] == '$')
			i++;
		else
			str[j++] = s[i++];
		if (s[i] == '\'' || s[i] == ' ')
			break ;
	}
	str[j] = '\0';
	if (is_a_quote(str))
		return (free(str), NULL);
	return (str);
}

void	remove_d_quotes(int d_quotes, int s_quotes, char *arg, char *s)
{
	if (d_quotes > 0 && s_quotes > 0)
	{
		if (d_quotes % 2 == 0)
		{
			s = ft_remove_squotes(arg);
			free(arg);
			arg = ft_strdup(s);
			free(s);
		}
	}
}

void	remove_s_quotes(int d_quotes, int s_quotes, char *arg, char *s)
{
	if (d_quotes > 1 && s_quotes > 0)
	{
		if (s_quotes % 2 == 0)
		{
			s = ft_remove_dquotes(arg);
			free(arg);
			arg = ft_strdup(s);
			free(s);
		}
	}
}

void	time_to_remove(t_mini *mini, int i)
{
	int		d_quotes;
	int		s_quotes;
	char	*s;

	s = NULL;
	d_quotes = count_dquote_pairs(mini->args[i]);
	s_quotes = count_squote_pairs(mini->args[i]);
	if (ft_strstartswith(mini->args[i], "\""))
		remove_d_quotes(d_quotes, s_quotes, mini->args[i], s);
	s_quotes = count_squote_pairs(mini->args[i]);
	if (ft_strstartswith(mini->args[i], "\'"))
		remove_s_quotes(d_quotes, s_quotes, mini->args[i], s);
}

void	ohhh_boy(t_mini *mini, int i)
{
	char	*s;

	s = ft_strdup(mini->args[i]);
	free(mini->args[i]);
	mini->args[i] = ft_remove_squotes(s);
	free(s);
}
