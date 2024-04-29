/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:23:27 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:25:29 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_expand2(t_mini *mini, int flag, int i, char **s)
{
	if (flag)
	{
		mini->before = ft_before(s[i]);
		mini->after = ft_after(s[i]);
	}
	else
	{
		free(mini->before);
		free(mini->after);
	}
}

int	get_qmark(t_mini *mini, int i, char **str)
{
	int		j;
	char	*before;
	char	*after;
	char	*temp;

	j = 0;
	while (str[i])
	{
		if (str[i][j] == '?')
		{
			free(str[i]);
			temp = ft_itoa(g_signal);
			before = ft_strjoin(mini->before, temp);
			after = ft_strjoin(before, mini->after);
			str[i] = ft_strdup(after);
			free(before);
			free(after);
			free(temp);
			return (1);
		}
		else
			j++;
	}
	return (0);
}

void	do_all(t_mini *mini, int i, char *env, char **s)
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
	s[i] = ft_strdup(temp);
	if (str)
		free(str);
	if (temp)
		free(temp);
}

int	expand_str(t_mini *mini, int i, char **str)
{
	char	*s;
	char	*env;

	if (ft_strstartswith(str[i], "\'"))
		return (ohhh_boy(str, i), 1);
	free_expand2(mini, 1, i, str);
	if (bingo(str[i], '?') && qmark_and_dollar(str[i]))
		get_qmark(mini, i, str);
	free_expand2(mini, 0, i, str);
	while (bingo(str[i], '$') && !quote_after_exp(str[i]))
	{
		free_expand2(mini, 1, i, str);
		s = get_expand(str[i]);
		if (exit_expand(s, mini))
			return (1);
		env = get_env(s, mini);
		free(s);
		free(str[i]);
		if (env)
			do_all(mini, i, env, str);
		else
			str[i] = ft_strjoin(mini->before, " ");
		free_expand2(mini, 0, i, str);
	}
	return (1);
}

void	check_comand(char **s, t_mini *mini)
{
	int	i;
	int	flag;

	i = -1;
	flag = 1;
	if (!s)
		return ;
	if (check_env(mini))
		return ;
	while (s[++i])
	{
		if (is_a_cmd(s[i], mini) || is_a_file(s[i]) || is_a_folder(s[i]))
		{
			if (count_quotes(s[i]) > 0)
				remove_quotes_helper(s, i);
		}
		if (condition_to_expand(i, s))
			flag = 0;
		if (bingo(s[i], '$') && ft_strlen(s[i]) > 1 && flag)
		{
			flag = 1;
			expand_str(mini, i, s);
		}
	}
}
