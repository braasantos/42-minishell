/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/06 15:53:49 by braasantos       ###   ########.fr       */
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

bool	is_special(char s)
{
	if (s == '_' || s == '=' || s == '\'' || s == '\"')
		return (false);
	if (!((s >= 65 && s <= 90) || (s >= 97 && s <= 122)))
		return (true);
	return (false);
}

int	check_var(char *s)
{
	if (is_special(s[0]) == true)
	{
		ft_putendl_fd(" not a valid identifier", 2);
		g_signal = 1;
		return (1);
	}
	return (0);
}

int	export_len(char **s)
{
	int i;
	int j;

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
	return (j);
}

char **coverup(char **str)
{
	int		j;
	char	**newarr;
	char	**result;
	int		i;

	j = export_len(str);
	newarr = (char **)malloc(sizeof(char *) * (j + 1));
	j = -1;
	i = 0;
	result = create_export(str, newarr, j, i);
	j = export_len(str);
	result[j++] = NULL;
	return (result);
}

void	return_merged(char *s, char **merged_string)
{
	char	*temp;

	temp = ft_strjoin(*merged_string, " ");
	free(*merged_string);
	*merged_string = ft_strjoin(temp, s);
	free(temp);
}

char **create_export(char **str, char **newarr, int j, int i)
{
	char	*merged_string;

	while (str[i])
	{
		merged_string = ft_strdup(str[i]);
		if (count_dquotes(str[i]) == 1 || count_squotes(str[i]) == 1)
		{
			while (str[i + 1] && (count_dquotes(str[i + 1]) != 1 && count_squotes(str[i + 1]) != 1))
			{
				return_merged(str[i + 1], &merged_string);
				i++;
			}
			if (str[i + 1])
			{
				return_merged(str[i + 1], &merged_string);
				i++;
			}
		}
		newarr[++j] = malloc(sizeof(char) * (ft_strlen(merged_string) + 1));
		ft_strcpy(newarr[j], merged_string);
		i++;
		free(merged_string);
	}
	return (newarr);
}

void	change_args(t_mini *mini)
{
	char	**args;

	args = get_newenvp(mini->args);
	ft_free_arr(mini->args);
	mini->args = coverup(args);
	ft_free_arr(args);
}

int	get_export(t_mini *mini)
{
	char	**newvar;
	int		flag;
	int		i;

	newvar = NULL;
	i = 1;
	if (!mini->args[1])
	{
		export_no_option(mini);
		return (1);
	}
	change_args(mini);
	while (mini->args[i] && !check_options(mini->args[i]))
	{
		flag = 0;
		if (check_var(mini->args[i]))
			return (1);
		if (var_exists(mini, mini->args[i]))
			delete_replace(mini, newvar, i, &flag);
		if (count_quotes(mini->new_str) == 0 && !flag)
			export_quotes(newvar, mini, i);
		else if (count_quotes(mini->new_str) > 0 && !flag)
			export_woquotes(newvar, mini, i);
		i++;
	}
	return (1);
}

void	delete_replace(t_mini *mini, char **str, int i, int *flag)
{
	*flag = 1;
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
