/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:24:11 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:24:12 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*return_var(char *s)
{
	char	*tmp;
	char	*var_name;

	tmp = ft_strdup(s);
	if (find_char('=', s))
		var_name = ft_strjoin(tmp, "=");
	else
		var_name = ft_strdup(tmp);
	free(tmp);
	return (var_name);
}

static void	free_unset(char **arr, char *str, int flag)
{
	if (flag)
	{
		if (arr)
		{
			ft_free_arr(arr);
			arr = NULL;
		}
	}
	if (!flag)
	{
		free(str);
		str = NULL;
	}
}

static void	free_all_exit(t_mini *mini, char **arr, char *str)
{
	free_unset(arr, NULL, 1);
	free_unset(mini->envp, NULL, 1);
	free_unset(NULL, str, 0);
}

int	get_unset(t_mini *mini)
{
	char	*var_name;
	char	**newvar;
	int		i;

	i = 1;
	newvar = NULL;
	while (mini->args[i])
	{
		if (var_exists(mini, mini->args[i]))
		{
			var_name = return_var(mini->args[i]);
			free_unset(newvar, NULL, 1);
			newvar = remove_var(mini->envp, var_name);
			if (*newvar == NULL)
				return (free_all_exit(mini, newvar, var_name), 1);
			ft_free_arr(mini->envp);
			mini->envp = NULL;
			mini->envp = ft_arrcpy(newvar);
			free_unset(newvar, var_name, 0);
		}
		i++;
	}
	free_unset(newvar, NULL, 1);
	return (1);
}
