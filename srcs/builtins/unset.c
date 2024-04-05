/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:04:04 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/05 15:50:16 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**remove_var(char **newenvp, char *var_name)
{
	int		num_vars;
	int		i;
	int		j;
	char	**newenvp_new;

	num_vars = 0;
	while (newenvp[num_vars])
		num_vars++;
	newenvp_new = (char **)malloc((num_vars + 1) * sizeof(char *));
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

int	get_unset(t_mini *mini)
{
	char	*var_name;
	char	**newvar;
	char	*temp;
	int		i;

	i = 1;
	while (mini->args[i])
	{
		temp = ft_strdup(mini->args[i]);
		if (find_char('=', mini->args[i]))
			var_name = ft_strjoin(temp, "=");
		else
			var_name = ft_strdup(temp);
		free(temp);
		newvar = remove_var(mini->newenvp, var_name);
		ft_free_arr(mini->newenvp);
		mini->newenvp = get_newenvp(newvar);
		ft_free_arr(newvar);
		free(var_name);
		i++;
	}
	return (1);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
