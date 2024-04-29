/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:30:00 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:30:03 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_fork_here_doc(t_mini *mini)
{
	free(mini->pwd);
	ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->envp)
		ft_free_arr(mini->envp);
	exit(g_signal);
}

void	return_new_delimiter(char *delimiter, t_mini *mini)
{
	if (mini->new_delimiter)
	{
		free(mini->new_delimiter);
		mini->new_delimiter = NULL;
	}
	if (count_quotes(delimiter) > 0)
		mini->new_delimiter = ft_remove_quotes(delimiter);
	else
		mini->new_delimiter = ft_strdup(delimiter);
}

t_mini	*return_mini(t_mini *newmini)
{
	static t_mini	mini;

	if (newmini)
		ft_memcpy(&mini, newmini, sizeof(t_mini));
	return (&mini);
}

int	exit_expand_heredoc(char *s, t_mini *mini)
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

void	free_expand2_heredoc(t_mini *mini, int flag, char *s)
{
	if (flag)
	{
		mini->before = ft_before(s);
		mini->after = ft_after(s);
	}
	else
	{
		free(mini->before);
		free(mini->after);
	}
}
