/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:23:47 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	var_exists(t_mini *mini, char *var)
{
	int		i;
	char	*new_var;

	i = 0;
	new_var = get_var(var);
	if (!mini->envp)
		return (0);
	while (mini->envp[i])
	{
		if (!ft_strncmp(mini->envp[i], new_var, ft_strlen(new_var)))
		{
			free(new_var);
			return (1);
		}
		i++;
	}
	free(new_var);
	return (0);
}

static bool	is_special(char s)
{
	if (s == '_' || s == '\'' || s == '\"')
		return (false);
	if (ft_isdigit(s))
	{
		return (false);
	}
	if (!((s >= 65 && s <= 90) || (s >= 97 && s <= 122)))
		return (true);
	return (false);
}

int	check_var(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '=' || ft_isdigit(s[i])
		|| s[i] == '_' || s[i] == '\'' || s[i] == '\"')
	{
		ft_fprintf(2, "Minishell: not a valid identifier\n");
		g_signal = 1;
		return (1);
	}
	while (s[i] && s[i] != '=')
	{
		if (is_special(s[i]) == true)
		{
			ft_fprintf(2, "Minishell: not a valid identifier\n");
			g_signal = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	export_len(char **s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (count_dquotes(s[i]) == 1 || count_squotes(s[i]) == 1)
		{
			while (s[i + 1] && (count_dquotes(s[i + 1]) != 1
					&& count_squotes(s[i + 1]) != 1))
				i++;
			if (s[i + 1])
				i++;
		}
		i++;
		j++;
	}
	ft_printf("%d\n", j);
	return (j);
}

void	get_export(t_mini *mini)
{
	char	**newvar;
	int		flag;
	int		i;

	newvar = NULL;
	i = 1;
	while (mini->args[i] && !check_options(mini->args[i]))
	{
		flag = 0;
		if (check_var(mini->args[i]))
		{
			i++;
			continue ;
		}
		if (var_exists(mini, mini->args[i]))
			delete_replace(mini, newvar, i, &flag);
		if (count_quotes(mini->new_str) == 0 && !flag)
			export_quotes(newvar, mini, i);
		else if (count_quotes(mini->new_str) > 0 && !flag)
			export_woquotes(newvar, mini, i);
		if (mini->args[i])
			i++;
	}
	if (!mini->args[1] || pipe_or_append(mini->args[1]))
		export_no_option(mini);
}
