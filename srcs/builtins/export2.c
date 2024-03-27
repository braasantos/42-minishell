/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:59:57 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/27 17:49:55 by bjorge-m         ###   ########.fr       */
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
void	get_alpha(char **str)
{
	int		i;
	// int		j;
	// int		n;
	// char	*temp;

	i = 0;
	// j = 0;
	// temp = NULL;
	// n = str_len(str);
	while_loop(str);
	int j;
	if (str[ i + 1])
		j = ft_strcmp(str[i], str[i]);
	printf("%d\n", j);
	// while (i <= n)
	// {
	// 	while(j <= n - i)
	// 	{
	// 		if (ft_strcmp(str[i], str[i+ 1]) > 0)
	// 		{
	// 			temp =  str[i];
	// 			str[i] = str[i + 1];
	// 			str[i + 1] = temp;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
}

char	**bb_sort(char **s)
{
	int		i;
	char	*temp;
	char	*t;
	char	**str;

	i = 0;
	while (s[i])
	{
		temp = export_var(s[i]);
		t = ft_strjoin(temp, " ");
		free(temp);
		i++;
	}
	str = ft_split(t, ' ');
	return (str);
}

void	export_no_option(t_mini *mini)
{
	char	**env;
	char	**temp;
	char	*value;
	char	*key;
	char	*tempv;
	char	*tempk;
	int		i;

	i = -1;
	temp = get_newenvp(mini->newenvp);
	env = bb_sort(temp);
	// while_loop(env);
	while (env[++i])
	{
		value = export_var(env[i]);
		key = export_key(env[i]);
		tempv = ft_strjoin("declare -x ", value);
		tempk = ft_strjoin(tempv, "\"");
		free(tempv);
		tempv = ft_strjoin(tempk, key);
		free(tempk);
		tempk = ft_strjoin(tempv, "\"");
		// printf("%s\n", tempk);
		free(tempk);
		free(tempv);
		free(value);
		free(key);
	}
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
