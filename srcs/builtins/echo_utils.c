/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/04/15 17:22:08 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char **new_args(char **s, int k, int k1)
{
	char **newenvp;
	int i;
	int j;
	int len;
	int new_index;

	len = str_len(s);
	newenvp = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	new_index = 0;
	while (i < len)
	{
		if (i != k && i != k1)
		{
			j = ft_strlen(s[i]);
			newenvp[new_index] = (char *)malloc((j + 1) * sizeof(char));
			if (newenvp[new_index] == NULL)
				return (free(newenvp), NULL);
			ft_strcpy(newenvp[new_index], s[i]);
			new_index++;
		}
		i++;
	}
	newenvp[new_index] = NULL;
	return (newenvp);
}

char	**echo_w_red(char **s)
{
	int		i;
	int		k1;
	char	**str;

	i = -1;
	str = NULL;
	while (s[++i])
	{
		if (is_a_red(s[i]))
		{
			k1 = i + 1;
			if (s[k1])
			{
				if (!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>"))
					if (file_ok(s[k1], 1))
						return (NULL);
				if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], "<<"))
					if (file_ok(s[k1], 2))
						return (NULL);
			}
			str = new_args(s, i, k1);
			return (str);
		}
	}
	return (str);
}

int	have_redi(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0)
			return (1);
		if (ft_strcmp(s[i], "<") == 0)
			return (1);
		if (ft_strcmp(s[i], ">>") == 0)
			return (1);
		if (ft_strcmp(s[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int echo_len(char **s, int i)
{
	while (s[i])
	{
		if (ft_strcmp(s[i], "|") == 0)
			return (i);
		i++;
	}
	return (i);
}

char **forming_echo_args(char **s, int i)
{
	char	**new_args;
	char	**str;
	int		j;
	
	str = get_newenvp(s);
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


int	havehere_doc(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "<<"))
			return (i);
		i++;
	}
	return (0);
}

void	heredoc_first(t_mini *mini)
{
	int	here_pos;
	int	delimiter_pos;
	char **s;
	int	i;

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
		if (!ft_strcmp(s[0] ,"NULL"))
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


int	condition_to_expand(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "<<"))
	{
		if (mini->args[i + 1])
		{
			if (bingo(mini->args[i + 1], '$'))
					return (1);
		}
	}
	if (bingo(mini->args[i], '\''))
			time_to_remove(mini, i);
	return (0);
}
void	check_comand(t_mini *mini)
{
	int		i;
	char	*temp;
	int		flag;

	i = 0;
	flag = 1;
	if (!mini->args)
		return ;
	while (mini->args[i])
	{
		if (is_a_cmd(mini->args[i], mini) || is_a_file(mini->args[i]) || is_a_folder(mini->args[i]))
		{
			if (count_quotes(mini->args[i]) > 0)
			{
				temp = ft_strdup(mini->args[i]);
				free(mini->args[i]);
				mini->args[i] = ft_remove_quotes(temp);
				free(temp);
			}
		}
		if (condition_to_expand(mini, i))
				flag = 0;
		if (bingo(mini->args[i], '$') && ft_strlen(mini->args[i]) > 1 && flag)
		{
			flag = 1;
			expand_str(mini, i);
		}
		i++;
	}
}

int count_dquote_pairs(char *str)
{
	int pairs;
	int open_quote;
	int i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			if (open_quote == 0)
				open_quote = 1;
			else
			{
				pairs++;
				open_quote = 0;
			}
		}
		i++;
	}
	return (pairs);
}
int count_squote_pairs(char *str)
{
	int pairs;
	int open_quote;
	int i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (open_quote == 0)
				open_quote = 1;
			else
			{
				pairs++;
				open_quote = 0;
			}
		}
		i++;
	}
	return (pairs);
}