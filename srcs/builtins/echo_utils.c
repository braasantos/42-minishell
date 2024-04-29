/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:23:14 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:23:16 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**echo_w_red(char **s)
{
	int		i;
	int		j;
	char	**str;

	i = -1;
	str = NULL;
	while (s[++i])
	{
		if (!ft_strcmp(s[i], ">>")
			|| !ft_strcmp(s[i], ">") || !ft_strcmp(s[i], "<"))
		{
			j = i + 1;
			str = new_args(s, i, j);
			return (str);
		}
	}
	return (str);
}

int	echo_len(char **s, int i)
{
	while (s[i])
	{
		if (ft_strcmp(s[i], "|") == 0)
			return (i);
		i++;
	}
	return (i);
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
		if (hanlde_redirects(mini, mini->echo_split, 0))
			return (1);
		s = echo_w_red(mini->echo_split);
		if (!ft_strcmp(s[0], "NULL"))
			return (g_signal = 1, 1);
		ft_free_arr(mini->echo_split);
		mini->echo_split = NULL;
		mini->echo_split = ft_arrcpy(s);
		mini->echo_flag = 1;
		ft_free_arr(s);
		return (0);
	}
	return (0);
}

char	**forming_echo_args(char **s, int i)
{
	char	**new_args;
	char	**str;
	int		j;

	str = ft_arrcpy(s);
	j = 0;
	new_args = (char **)malloc(sizeof(char *) * (echo_len(s, i) + 1));
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") != 0)
		{
			new_args[j] = ft_strdup(str[i]);
			j++;
		}
		else
		{
			ft_free_arr(str);
			new_args[j] = NULL;
			return (new_args);
		}
		i++;
	}
	new_args[j] = NULL;
	ft_free_arr(str);
	return (new_args);
}

void	check_echo(t_mini *mini)
{
	char	**s;
	int		pos_red;
	int		pos_file;

	s = NULL;
	while (have_redi(mini->echo_split))
	{
		pos_red = check_pos_str(mini->echo_split);
		pos_file = pos_red + 1;
		if (s)
		{
			ft_free_arr(s);
			s = NULL;
		}
		s = new_args(mini->echo_split, pos_red, pos_file);
		if (mini->echo_split)
		{
			ft_free_arr(mini->echo_split);
		}
		mini->echo_split = ft_arrcpy(s);
		ft_free_arr(s);
	}
}
