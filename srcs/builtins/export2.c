/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/04 18:18:53 by bjorge-m         ###   ########.fr       */
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

bool	is_special(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '_' || s[i] == '=')
			return (false);
		if (!((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)))
			return (true);
		i++;
	}
	return (false);
}

int	check_var(t_mini *mini)
{
	int	i;

	i = 1;
	while (mini->args[i])
	{
		// if (mini->args[i][0] == '_')
		// 	return (0);
		if (is_special(mini->args[i]) == true)
		{
			ft_putendl_fd(" not a valid identifier", 2);
			g_signal = 1;
			return (1);
		}
		i++;
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
		if (check_var(mini))
			return (1);
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
