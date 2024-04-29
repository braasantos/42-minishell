/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:23:52 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:23:53 by bjorge-m         ###   ########.fr       */
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

int	export_wo_equal(char *s, char *c)
{
	if (bingo(s, '='))
		return (0);
	else
	{
		ft_printf("%s\n", s);
		free(s);
		free(c);
		return (1);
	}
	return (0);
}

int	export_unset(t_mini *mini, int i)
{
	char	*var_name;
	char	**newvar;

	if (mini->args[i])
	{
		var_name = get_var(mini->args[i]);
		newvar = remove_var(mini->envp, var_name);
		ft_free_arr(mini->envp);
		mini->envp = ft_arrcpy(newvar);
		ft_free_arr(newvar);
		free(var_name);
	}
	return (1);
}

void	export_no_option(t_mini *mini)
{
	char	**env;
	char	*key;
	char	*tempv;
	char	*tempk;
	int		i;

	i = -1;
	env = get_alpha(mini->envp);
	while (env[++i])
	{
		key = export_key(env[i]);
		tempv = export_no_option_util(env[i]);
		if (export_wo_equal(tempv, key))
			continue ;
		tempk = ft_strjoin(tempv, "\"");
		free(tempv);
		tempv = ft_strjoin(tempk, key);
		free(tempk);
		tempk = ft_strjoin(tempv, "\"");
		ft_printf("%s\n", tempk);
		free(tempk);
		free(tempv);
		free(key);
	}
}

char	**add_var(char **newenvp, char *new_var)
{
	int		num_vars;
	int		i;
	char	**newenvp_new;

	num_vars = arr_len(newenvp);
	i = 0;
	newenvp_new = ft_calloc((num_vars + 2), sizeof(char *));
	if (newenvp_new == NULL)
		return (NULL);
	while (i < num_vars)
	{
		newenvp_new[i] = ft_calloc((ft_strlen(newenvp[i]) + 1), sizeof(char));
		ft_strcpy(newenvp_new[i], newenvp[i]);
		i++;
	}
	newenvp_new[num_vars] = ft_calloc((ft_strlen(new_var) + 1), sizeof(char));
	ft_strcpy(newenvp_new[num_vars], new_var);
	newenvp_new[num_vars + 1] = NULL;
	return (newenvp_new);
}
