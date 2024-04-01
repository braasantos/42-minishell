/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/04/01 18:30:06 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*hndl_quotes_echo(t_mini *mini, int i)
{
	char	*s;
	char	*temp;

	s = NULL;
	temp = NULL;
	s = ft_strdup(mini->args[i]);
	temp = ft_strjoin(s, " ");
	free(s);
	return (temp);
}

int	save_lines3(t_mini *mini, char *temp, int i)
{
	if (is_a_pipe(mini->args[i]))
	{
		mini->pipe_or_redirect_found = true;
		free(temp);
		return (1);
	}
	return (0);
}

char	**add_option_echo(t_mini *mini, int i, char *temp)
{
	char	*result;
	char	*new_result;
	char	**ret;

	result = NULL;
	mini->pipe_or_redirect_found = false;
	while (mini->args[i] && !mini->pipe_or_redirect_found)
	{
		temp = hndl_quotes_echo(mini, i);
		if (result == NULL)
			result = ft_strdup(temp);
		else
		{
			if (save_lines3(mini, temp, i))
				break ;
			new_result = ft_strjoin(result, temp);
			free(result);
			result = ft_strdup(new_result);
			free(new_result);
		}
		free(temp);
		i++;
	}
	ret = ft_split(result, ' ');
	return (free(result), ret);
}

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
		if (!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], "<") || 
			!ft_strcmp(s[i], ">>") || !ft_strcmp(s[i], "<<"))
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
		}
	}
	return (str);
}

int	handle_split_args(t_mini *mini, int i)
{
	char	*temp;
	char	**s;

	temp = NULL;
	mini->free_flag = 0;
	mini->echo_split = add_option_echo(mini, i, temp);
	if (have_redirect(mini))
	{
		s = echo_w_red(mini->echo_split);
		if (!ft_strcmp(s[0] ,"NULL"))
			return (1);
		ft_free_arr(mini->echo_split);
		mini->echo_split = get_newenvp(s);
		mini->echo_flag = 1;
		return (0);
	}
	return (0);
}

void	check_comand(t_mini *mini)
{
	int		i;
	char	*temp;

	i = 0;
	if (!mini->args)
		return ;
	while (mini->args[i])
	{
		if (is_a_cmd(mini->args[i], mini))
		{
			if (count_quotes(mini->args[i]) > 0)
			{
				temp = ft_strdup(mini->args[i]);
				free(mini->args[i]);
				mini->args[i] = ft_remove_quotes(temp);
				free(temp);
			}
		}
		if (!have_here_doc(mini))
			if (bingo(mini->args[i], '$') && ft_strlen(mini->args[i]) > 1)
				expand_str(mini, i);
		if (bingo(mini->args[i], '\''))
			time_to_remove(mini, i);
		i++;
	}
}

int count_quote_pairs(char *str)
{
	int pairs;
	int open_quote;
	int i;

	pairs = 0;
	open_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
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
