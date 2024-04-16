/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:56:25 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 19:50:23 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_first(t_mini *mini)
{
	char	**s;
	int		here_pos;
	int		delimiter_pos;
	int		i;

	i = 0;
	if (havehere_doc(mini->echo_split))
	{
		here_pos = havehere_doc(mini->echo_split);
		delimiter_pos = here_pos + 1;
		while (mini->echo_split[i])
		{
			if (!ft_strcmp(mini->echo_split[i], "<<"))
				handle_heredoc(mini, mini->echo_split[i + 1]);
			i++;
		}
		s = new_args(mini->echo_split, here_pos, delimiter_pos);
		if (mini->echo_split)
		{
			ft_free_arr(mini->echo_split);
			mini->echo_split = NULL;
		}
		mini->echo_split = get_newenvp(s);
		ft_free_arr(s);
	}
}

int	handle_split_args(t_mini *mini, int i)
{
	char	**s;

	mini->free_flag = 0;
	if (mini->echo_split)
	{
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
	}
	mini->echo_split = forming_echo_args(mini->args, i);
	if (have_redi(mini->echo_split))
	{
		heredoc_first(mini);
		if (hanlde_redirects(mini, mini->echo_split, 0, 0))
			return (1);
		s = echo_w_red(mini->echo_split);
		if (!ft_strcmp(s[0], "NULL"))
			return (g_signal = 1, 1);
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
		mini->echo_split = get_newenvp(s);
		mini->echo_flag = 1;
		ft_free_arr(s);
		return (0);
	}
	return (0);
}

void	remove_quotes_helper(t_mini *mini, int i)
{
	char	*temp;

	temp = ft_strdup(mini->args[i]);
	free(mini->args[i]);
	mini->args[i] = ft_remove_quotes(temp);
	free(temp);
}

int	check_things(char *s)
{
	char *str;

	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (!ft_strcmp(str, ">"))
		return (free(str), 1);
	if (!ft_strcmp(str, "<"))
		return (free(str), 1);
	if (!ft_strcmp(str, "|"))
		return (free(str), 1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (free(str), 1);
	return (free(str), 0);
}

void	check_comand(t_mini *mini)
{
	int		i;
	int		flag;

	i = -1;
	flag = 1;
	if (!mini->args)
		return ;
	while (mini->args[++i])
	{
		if (is_a_cmd(mini->args[i], mini)
			|| is_a_file(mini->args[i]) 
			|| is_a_folder(mini->args[i]))
		{
			if (count_quotes(mini->args[i]) > 0)
				remove_quotes_helper(mini, i);
		}
		if (condition_to_expand(mini, i))
			flag = 0;
		if (bingo(mini->args[i], '$') && ft_strlen(mini->args[i]) > 1 && flag)
		{
			flag = 1;
			expand_str(mini, i);
		}
	}
}
