/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:29:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:29:58 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_all_heredoc(t_mini *mini, char *env, char **s)
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
	*s = ft_strdup(temp);
	if (str)
		free(str);
	if (temp)
		free(temp);
}

int	get_qmark_heredoc(t_mini *mini, char **str)
{
	char	*before;
	char	*after;
	char	*temp;
	int		i;

	i = 0;
	while (*str[i])
	{
		if (*str[i] == '?')
		{
			free(*str);
			temp = ft_itoa(g_signal);
			before = ft_strjoin(mini->before, temp);
			after = ft_strjoin(before, mini->after);
			*str = ft_strdup(after);
			free(before);
			free(after);
			free(temp);
			return (1);
		}
		else
			i++;
	}
	return (0);
}

int	quote_after_exp_hereodc(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '$')
		i++;
	if (s[i] == '\"')
		return (1);
	return (0);
}

void	redirect(t_mini *mini)
{
	dup2(mini->stdin_fd, STDIN_FILENO);
	dup2(mini->stdout_fd, STDOUT_FILENO);
}

int	doredirect(char ***s, t_mini *mini)
{
	char	**str;

	if (count_pipes(*s) == 0)
	{
		if (count_files(*s) > 1 && command(mini, *s))
		{
			str = echo_w_red(*s);
			if (!str)
			{
				g_signal = 1;
				return (1);
			}
			ft_free_arr(*s);
			*s = ft_arrcpy(str);
			ft_free_arr(str);
		}
	}
	return (0);
}
