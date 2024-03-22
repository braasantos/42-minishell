/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:21 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/21 13:03:07 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**add_var(char **newenvp, char *new_var)
{
	int		num_vars;
	int		i;
	char	**newenvp_new;

	num_vars = str_len(newenvp);
	i = 0;
	newenvp_new = malloc((num_vars + 2) * sizeof(char *));
	if (newenvp_new == NULL)
		return (NULL);
	while (i < num_vars)
	{
		newenvp_new[i] = malloc((ft_strlen(newenvp[i]) + 1) * sizeof(char));
		ft_strcpy(newenvp_new[i], newenvp[i]);
		i++;
	}
	newenvp_new[num_vars] = malloc((ft_strlen(new_var) + 1) * sizeof(char));
	ft_strcpy(newenvp_new[num_vars], new_var);
	newenvp_new[num_vars + 1] = NULL;
	return (newenvp_new);
}

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

int	export_unset(t_mini *mini)
{
	char	*var_name;
	char	**newvar;

	if (mini->args[1])
	{
		var_name = get_var(mini->args[1]);
		newvar = remove_var(mini->newenvp, var_name);
		ft_free_arr(mini->newenvp);
		mini->newenvp = get_newenvp(newvar);
		ft_free_arr(newvar);
		free(var_name);
	}
	return (1);
}

void	export_woquotes(char **newvar, t_mini *mini)
{
	char	**splitted;
	char	*str;
	char	*tmp;

	splitted = ft_split(mini->new_str, '\"');
	str = help(splitted[0]);
	tmp = ft_strjoin(str, splitted[1]);
	free(str);
	newvar = add_var(mini->newenvp, tmp);
	free(tmp);
	ft_free_arr(mini->newenvp);
	mini->newenvp = get_newenvp(newvar);
	ft_free_arr(newvar);
	ft_free_arr(splitted);
}

char	*ft_remove_squotes(const char *str)
{
	char	*new_str;
	size_t	len;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	len = strlen(str);
	new_str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (new_str == NULL)
		return (NULL);
	while (i < len)
	{
		if (str[i] != '\'')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
