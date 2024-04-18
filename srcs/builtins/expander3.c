/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:03:56 by gabe              #+#    #+#             */
/*   Updated: 2024/04/18 13:59:30 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	qmark_and_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (*str == '?')
				return (1);
			else
				return (0);
		}
		str++;
	}
	return (0);
}

void	free_expand2(t_mini *mini, int flag, int i)
{
	if (flag)
	{
		mini->before = ft_before(mini->args[i]);
		mini->after = ft_after(mini->args[i]);
	}
	else
	{
		free(mini->before);
		free(mini->after);
	}
}
int	expand_str(t_mini *mini, int i)
{
	char	*s;
	char	*env;

	if (count_squotes(mini->args[i]) > 0)
		return (ohhh_boy(mini, i), 1);
	free_expand2(mini, 1, i);
	if (bingo(mini->args[i], '?') && qmark_and_dollar(mini->args[i]))
		get_qmark(mini, i);
	free_expand2(mini, 0, i);
	while (bingo(mini->args[i], '$'))
	{
		free_expand2(mini, 1, i);
		s = get_expand(mini->args[i]);
		if (exit_expand(s, mini))
			return (1);
		env = get_env(s, mini);
		free(s);
		free(mini->args[i]);
		if (env)
			do_all(mini, i, env);
		else
			mini->args[i] = ft_strdup("1801");
		free_expand2(mini, 0, i);
	}
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
