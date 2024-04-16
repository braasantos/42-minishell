/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:00:10 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 14:01:23 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*ft_remove_dquotes(const char *str)
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
		if (str[i] != '\"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
