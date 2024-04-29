/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:27:24 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:28:09 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pwd(char *s, t_mini *mini)
{
	char	*key;
	int		i;

	i = -1;
	while (mini->envp[++i])
	{
		key = export_key(mini->envp[i]);
		if (!ft_strcmp(s, key))
		{
			if (ft_strchr(s, '/'))
			{
				ft_fprintf(2, "%s: Is a directory\n", s);
				return (free(key), g_signal = 126, 1);
			}
		}
		free(key);
	}
	return (0);
}

int	check_env(t_mini *mini)
{
	if (!mini->envp)
		return (1);
	return (0);
}

char	*get_env(char *var, t_mini *mini)
{
	int		i;
	char	*tmp;
	char	*str;

	i = -1;
	if (!var)
		return (NULL);
	str = ft_remove_quotes(var);
	tmp = ft_strjoin(str, "=");
	free(str);
	if (check_env(mini))
		return (NULL);
	while (mini->envp[++i])
	{
		if (ft_strstartswith(mini->envp[i], tmp))
		{
			free(tmp);
			return (ft_strchr(mini->envp[i], '=') + 1);
		}
	}
	free(tmp);
	if (is_a_quote(var))
		return (NULL);
	return (NULL);
}

int	ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

char	**remove_var(char **newenvp, char *var_name)
{
	int		num_vars;
	int		i;
	int		j;
	char	**newenvp_new;

	newenvp_new = NULL;
	num_vars = arr_len(newenvp);
	newenvp_new = ft_calloc((num_vars), sizeof(char *));
	if (newenvp_new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < num_vars)
	{
		if (ft_strncmp(newenvp[i], var_name, ft_strlen(var_name)) != 0)
		{
			newenvp_new[j] = ft_strdup(newenvp[i]);
			j++;
		}
		i++;
	}
	newenvp_new[j] = NULL;
	return (newenvp_new);
}
