/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreir <gamoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/19 17:07:55 by gamoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_expand(char *s, t_mini *mini)
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
		if (!(ft_isalnum(s[i])))
			break ;
	}
	str[j] = '\0';
	mini->after = ft_after_expand(str, mini);
	if (is_a_quote(str))
		return (free(str), NULL);
	return (str);
}

void	remove_d_quotes(int i, t_mini *mini, char *s)
{
	int	d_quotes;
	int	s_quotes;

	d_quotes = count_dquote_pairs(mini->args[i]);
	s_quotes = count_squote_pairs(mini->args[i]);
	if (d_quotes > 0 && s_quotes > 0)
	{
		if (d_quotes % 2 == 0)
		{
			s = ft_remove_squotes(mini->args[i]);
			free(mini->args[i]);
			mini->args[i] = ft_strdup(s);
			free(s);
		}
	}
}

void	remove_s_quotes(int i, t_mini *mini, char *s)
{
	int	d_quotes;
	int	s_quotes;

	d_quotes = count_dquote_pairs(mini->args[i]);
	s_quotes = count_squote_pairs(mini->args[i]);
	if (s_quotes >= 2)
	{
		if (s_quotes % 2 == 0)
		{
			s = ft_remove_squotes(mini->args[i]);
			free(mini->args[i]);
			mini->args[i] = ft_strdup(s);
			free(s);
		}
	}
	else if ((d_quotes > 1 && s_quotes > 0))
	{
		if (s_quotes % 2 == 0)
		{
			s = ft_remove_dquotes(mini->args[i]);
			free(mini->args[i]);
			mini->args[i] = ft_strdup(s);
			free(s);
		}
	}
}

void	time_to_remove(t_mini *mini, int i)
{
	char	*s;

	s = NULL;
	if (ft_strstartswith(mini->args[i], "\""))
		remove_d_quotes(i, mini, s);
	if (ft_strstartswith(mini->args[i], "\'"))
		remove_s_quotes(i, mini, s);
}

void	ohhh_boy(t_mini *mini, int i)
{
	char	*s;

	s = ft_strdup(mini->args[i]);
	free(mini->args[i]);
	mini->args[i] = ft_remove_squotes(s);
	free(s);
}
void	helper(t_mini *mini, int i, char *s, int flag)
{
	char	*antes;
	char	*depois;

	if (flag)
	{
		s = ft_remove_dquotes(mini->args[i]);
		antes = ft_strjoin("\"", s);
		depois = ft_strjoin(antes, "\"");
	}
	else
	{
		s = ft_remove_squotes(mini->args[i]);
		antes = ft_strjoin("\'", s);
		depois = ft_strjoin(antes, "\'");
	}
	free(mini->args[i]);
	mini->args[i] = ft_strdup(depois);
	free(antes);
	free(depois);
	free(s);
}

int	remove_quotes_exp(t_mini *mini, int i)
{
	int		d_quotes;
	int		s_quotes;
	char	*s;

	s = NULL;
	d_quotes = count_dquote_pairs(mini->args[i]);
	s_quotes = count_squote_pairs(mini->args[i]);
	if (d_quotes > 0 && s_quotes > 0)
	{
		if (ft_strstartswith(mini->args[i], "\""))
		{
			if (d_quotes % 2 != 0)
				helper(mini, i, s, 1);
			else
				return (ohhh_boy(mini, i), 1);
		}
		else if (ft_strstartswith(mini->args[i], "\'"))
		{
			if (s_quotes % 2 != 0)
				helper(mini, i, s, 0);
			else
				return (ohhh_boy(mini, i), 1);
		}
		else
			return (ohhh_boy(mini, i), 1);
	}
	else if ( s_quotes > 0 && d_quotes == 0 )
		return (ohhh_boy(mini, i), 1);
	return (0);
}
