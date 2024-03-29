/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/29 17:00:44 by braasantos       ###   ########.fr       */
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
int	check_var(t_mini *mini, int i)
{
	int	j;

	j = 0;
	while(mini->args[i][j])
	{
		if (!ft_isalpha(mini->args[i][j]))
			return (1);
		j++;
	}
	return (0);
}


int	get_export(t_mini *mini)
{
	char	**newvar;
	int		i;

	newvar = NULL;
	i = 0;
	while (mini->args[++i] && !check_options(mini->args[i]))
	{
		if (!ft_isalpha(mini->args[i][0]) || check_var(mini, i))
		{
			ft_printf("Minishell: export: `%s': ", mini->args[i]);
			return (ft_printf("not a valid identifier\n"), 1);
		}
		if (var_exists(mini, mini->args[i]))
		{
			delete_replace(mini, newvar, i);
			return (1);
		}
		if (count_quotes(mini->new_str) == 0)
			export_quotes(newvar, mini, i);
		else if (count_quotes(mini->new_str) > 0)
			export_woquotes(newvar, mini, i);
	}
	if (!mini->args[1])
		export_no_option(mini);
	return (1);
}

void	delete_replace(t_mini *mini, char **str, int i)
{
	export_unset(mini);
	if (count_quotes(mini->new_str) == 0)
		export_quotes(str, mini, i);
	else if (count_quotes(mini->new_str) > 0)
		export_woquotes(str, mini, i);
}

void	export_quotes(char **newvar, t_mini *mini, int i)
{
	char	*var;

	var = ft_strdup(mini->args[i]);
	newvar = add_var(mini->newenvp, var);
	ft_free_arr(mini->newenvp);
	mini->newenvp = get_newenvp(newvar);
	ft_free_arr(newvar);
	free(var);
}
