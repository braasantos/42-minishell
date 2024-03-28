/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:05:54 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/28 12:16:52 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_alpha(char **str)
{
	int		i;
	int		j;
	int		n;
	char	*temp;

	n = 0;
	while (str[n] != NULL)
		n++;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (str[j + 1] != NULL && ft_strcmp(str[j], str[j + 1]) > 0)
			{
				temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (str);
}

char	**bb_sort(char **s)
{
	int		i;
	char	*temp;
	char	*t;
	char	**str;
	char	*new_t;

	t = NULL;
	i = -1;
	while (s[++i] != NULL)
	{
		temp = ft_strdup(s[i]);
		if (t == NULL)
			t = strdup(temp);
		else
		{
			new_t = ft_strjoin(t, temp);
			free(t);
			t = ft_strjoin(new_t, " ");
			free(new_t);
		}
		free(temp);
	}
	str = ft_split(t, ' ');
	free(t);
	return (str);
}

char	*export_no_option_util(char *s)
{
	char	*value;
	char	*tempv;

	value = export_var(s);
	tempv = ft_strjoin("declare -x ", value);
	free(value);
	return (tempv);
}

void	export_no_option(t_mini *mini)
{
	char	**env;
	char	*key;
	char	*tempv;
	char	*tempk;
	int		i;

	i = -1;
	env = get_alpha(bb_sort(mini->newenvp));
	while (env[++i])
	{
		key = export_key(env[i]);
		tempv = export_no_option_util(env[i]);
		tempk = ft_strjoin(tempv, "\"");
		free(tempv);
		tempv = ft_strjoin(tempk, key);
		free(tempk);
		tempk = ft_strjoin(tempv, "\"");
		printf("%s\n", tempk);
		free(tempk);
		free(tempv);
		free(key);
	}
	ft_free_arr(env);
}
