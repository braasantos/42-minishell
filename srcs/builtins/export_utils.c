/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:24:00 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:24:01 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var(char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && s[i] != '=')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
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
	newvar = add_var(mini->envp, var);
	ft_free_arr(mini->envp);
	mini->envp = ft_arrcpy(newvar);
	ft_free_arr(newvar);
	free(var);
}

void	export_woquotes(char **newvar, t_mini *mini, int i)
{
	char	*tmp;

	tmp = ft_remove_quotes(mini->args[i]);
	newvar = add_var(mini->envp, tmp);
	free(tmp);
	ft_free_arr(mini->envp);
	mini->envp = ft_arrcpy(newvar);
	ft_free_arr(newvar);
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
