/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/05 18:00:33 by bjorge-m         ###   ########.fr       */
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

void	time_to_remove(t_mini *mini, int i)
{
	int		d_quotes;
	int		s_quotes;
	char	*s;

	d_quotes = count_quote_pairs(mini->new_str);
	s_quotes = count_squotes(mini->new_str);
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
	// if (d_quotes == 0 && s_quotes > 0)
	// 	ohhh_boy(mini, i);
}

void	ohhh_boy(t_mini *mini, int i)
{
	char	*s;

	s = ft_strdup(mini->args[i]);
	free(mini->args[i]);
	mini->args[i] = ft_remove_squotes(s);
	free(s);
}

int	exit_expand(char *s, t_mini *mini)
{
	if (!s)
	{
		free(s);
		free(mini->before);
		free(mini->after);
		return (1);
	}
	return (0);
}

int	expand_str(t_mini *mini, int i)
{
	char	*s;
	char	*env;
	int		count_quotes;

	count_quotes = count_dquotes(mini->new_str);
	if (count_quotes == 0 && count_squotes(mini->new_str) > 0)
		return (ohhh_boy(mini, i), 1);
	mini->before = ft_before(mini->args[i]);
	mini->after = ft_after(mini->args[i]);
	if (bingo(mini->args[i], '?'))
		get_qmark(mini, i);
	else
	{
		s = get_expand(mini->args[i]);
		env = get_env(s, mini);
		free(s);
		free(mini->args[i]);
		if (env)
			do_all(mini, i, env);
		else
			mini->args[i] = ft_strdup("1801");
	}
	free(mini->before);
	free(mini->after);
	return (1);
}

void	do_all(t_mini *mini, int i, char *env)
{
	char	*str;
	char	*temp;

	if (mini->before)
		str = ft_strjoin(mini->before, env);
	else
		str = ft_strdup(env);
	if (mini->after)
		temp = ft_strjoin(str, mini->after);
	else
		temp = ft_strdup(env);
	mini->args[i] = ft_strdup(temp);
	if (str)
		free(str);
	if (temp)
		free(temp);

}
