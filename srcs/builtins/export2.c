/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/09 13:55:45 by bjorge-m         ###   ########.fr       */
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
		if (s[i] == '_' || s[i] == '=' || s[i] == '\'' || s[i] == '\"')
			return (false);
		if (!((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)))
			return (true);
		i++;
	}
	return (false);
}

int	check_var(char **s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (is_special(s[i]) == true)
		{
			ft_putendl_fd(" not a valid identifier", 2);
			g_signal = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

char *create_export(char **str, t_mini *mini, int i)
{
    char **s;
    char *merged_string;
	char *temp;

	s = get_newenvp(str);
	merged_string = NULL;
    while (s[i])
	{
        if (count_dquotes(s[i]) == 1 || count_squotes(s[i]) == 1)
		{
            merged_string = ft_strdup(s[i]);
			free(s[i]);
			s[i] = NULL;
            while (s[i + 1] && (count_dquotes(s[i + 1]) != 1 && count_squotes(s[i + 1]) != 1))
			{
                temp = ft_strjoin(merged_string, " ");
                free(merged_string);
                merged_string = ft_strjoin(temp, s[i + 1]);
                free(temp);
                i++;
				free(s[i]);
				s[i] = NULL;
            }
            if (s[i + 1])
			{
                temp = ft_strjoin(merged_string, " ");
                free(merged_string);
                merged_string = ft_strjoin(temp, s[i + 1]);
                free(temp);
                i++;
				free(s[i]);
				s[i] = NULL;
            }
        }
        i++;
    }
	s[1] = ft_strdup(merged_string);
	s[2] = NULL;
	ft_free_arr(mini->args);
	mini->args = get_newenvp(s);
	return (merged_string);
}

int	get_export(t_mini *mini)
{
	char	**newvar;
	int		flag;
	int		i;

	newvar = NULL;
	i = 0;
	flag = 0;
	while_loop(mini->args);
	while (mini->args[++i] && !check_options(mini->args[i]))
	{
		flag = 0;
		if (check_var(mini->args))
			return (1);
		if (var_exists(mini, mini->args[i]))
		{
			flag = 1;
			delete_replace(mini, newvar, i);
		}
		if (count_quotes(mini->new_str) == 0 && !flag)
			export_quotes(newvar, mini, i);
		else if (count_quotes(mini->new_str) > 0 && !flag)
		{
			create_export(mini->args, mini, i);
			while_loop(mini->args);
			export_woquotes(newvar, mini, i);
		}
	}
	if (!mini->args[1])
		export_no_option(mini);
	return (1);
}

void	delete_replace(t_mini *mini, char **str, int i)
{
	export_unset(mini, i);
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
