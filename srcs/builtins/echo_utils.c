/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:31:07 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 18:48:17 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**new_args(char **s, int k, int k1)
{
	char	**newenvp;
	int		i;
	int		j;
	int		len;
	int		new_index;

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

char	**forming_echo_args(char **s, int i)
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
