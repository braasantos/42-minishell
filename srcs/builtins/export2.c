/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/28 10:19:24 by bjorge-m         ###   ########.fr       */
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


char	**bb_sort(char **s)
{
	int		i;
	char	*temp;
	char	*t;
	char	**str;
	char	*new_t;

	t = NULL;
	i = -1;
	while (s[++i] != NULL)
	{
		temp = ft_strdup(s[i]);
		if (t == NULL)
			t = strdup(temp);
		else
		{
			new_t = ft_strjoin(t, temp);
			free(t);
			t = ft_strjoin(new_t, " ");
			free(new_t);
		}
		free(temp);
	}
	str = ft_split(t, ' ');
	free(t);
	return (str);
}

char	*export_no_option_util(char *s)
{
	char	*value;
	char	*tempv;

	value = export_var(s);
	tempv = ft_strjoin("declare -x ", value);
	free(value);
	return (tempv);
}

void	export_no_option(t_mini *mini)
{
	char	**env;
	char	*key;
	char	*tempv;
	char	*tempk;
	int		i;

	i = -1;
	env = get_alpha(bb_sort(mini->newenvp));
	while (env[++i])
	{
		key = export_key(env[i]);
		tempv = export_no_option_util(env[i]);
		tempk = ft_strjoin(tempv, "\"");
		free(tempv);
		tempv = ft_strjoin(tempk, key);
		free(tempk);
		tempk = ft_strjoin(tempv, "\"");
		printf("%s\n", tempk);
		free(tempk);
		free(tempv);
		free(key);
	}
	ft_free_arr(env);
}


int	get_export(t_mini *mini)
{
	char	**newvar;

	newvar = NULL;
	if (mini->args[1] && !check_options(mini->args[1]))
	{
		if (ft_isdigit(mini->args[1][0]))
		{
			ft_printf("bash: export: `%s': ");
			ft_printf("not a valid identifier\n", mini->args[1]);
			return (1);
		}
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
	else
		export_no_option(mini);
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
