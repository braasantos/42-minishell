/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/21 13:00:14 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	var_exists(t_mini *mini, char *var)
{
	int		i;
	char	*new_var;

	i = 0;
	new_var = get_var(var);
	while (mini->newenvp[i])
	{
		if (!ft_strncmp(mini->newenvp[i], new_var, ft_strlen(new_var)))
		{
			free(new_var);
			return (1);
		}
		i++;
	}
	free(new_var);
	return (0);
}

int	get_export(t_mini *mini)
{
	char	**newvar;

	newvar = NULL;
	if (mini->args[1])
	{
		if (var_exists(mini, mini->args[1]))
		{
			delete_replace(mini, newvar);
			return (1);
		}
		if (count_quotes(mini->new_str) == 0)
			export_quotes(newvar, mini);
		else if (count_quotes(mini->new_str) > 0)
			export_woquotes(newvar, mini);
	}
	return (1);
}

void	delete_replace(t_mini *mini, char **str)
{
	export_unset(mini);
	if (count_quotes(mini->new_str) == 0)
		export_quotes(str, mini);
	else if (count_quotes(mini->new_str) > 0)
		export_woquotes(str, mini);
}

void	export_quotes(char **newvar, t_mini *mini)
{
	char	*var;

	var = ft_strdup(mini->args[1]);
	newvar = add_var(mini->newenvp, var);
	ft_free_arr(mini->newenvp);
	mini->newenvp = get_newenvp(newvar);
	ft_free_arr(newvar);
	free(var);
}
