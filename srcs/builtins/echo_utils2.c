/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:56:25 by gabe              #+#    #+#             */
/*   Updated: 2024/04/18 13:58:48 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	take_care(t_mini *mini, int flag, char **s)
{
	if (flag)
	{
		if (mini->echo_split)
		{
			ft_free_arr(mini->echo_split);
			mini->echo_split = NULL;
		}
		mini->echo_split = get_newenvp(s);
	}
	if (!flag)
	{
		if (mini->args)
		{
			ft_free_arr(mini->args);
			mini->args = NULL;
		}
		mini->args = get_newenvp(s);
	}
}

int	count_here(char **str, char *to_find)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], to_find))
			count++;
		i++;
	}
	return (count);
}

int	last_to_find(char **s, char *to_find)
{
	int	last_here;
	int	i;

	i = 0;
	last_here = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], to_find))
			last_here = i;
		i++;
	}
	return (last_here);
}
void	remove_here(t_mini *mini)
{
	int	i;
	int	last_here;
	char **s;

	i = 0;
	s = NULL;
	last_here = last_to_find(mini->args, "<<");
	if (count_here(mini->args, "<<") == 2)
	{
		while (mini->args[i])
		{
			if (!ft_strcmp(mini->args[i], "<<"))
			{
				if (i != last_here)
					s = new_args(mini->args, i, (i + 1));
				else
					break ;
			}
			i++;
		}
		ft_free_arr(mini->args);
		mini->args = NULL;
		mini->args = get_newenvp(s);
		ft_free_arr(s);
	}
}


void	heredoc_first(t_mini *mini, char **str, int flag)
{
	char	**s;
	int		here_pos;
	int		delimiter_pos;
	int		i;

	i = 0;
	(void)str;
	remove_here(mini);
	if (havehere_doc(mini->args) && str_len(mini->args) > 2)
	{
		here_pos = havehere_doc(mini->args);
		delimiter_pos = here_pos + 1;
		while (mini->args[i])
		{
			if (!ft_strcmp(mini->args[i], "<<"))
				handle_heredoc(mini, (mini->args[i + 1]));
			i++;
		}
		s = new_args(mini->args, here_pos, delimiter_pos);
		take_care(mini, flag, s);
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
		heredoc_first(mini, mini->echo_split, 1);
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
