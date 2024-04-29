/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:23:33 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:23:34 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_expand(char *s, t_mini *mini)
{
	if (!s)
	{
		free(s);
		free(mini->before);
		free(mini->after);
		return (1);
	}
	return (0);
}

void	ohhh_boy(char **str, int i)
{
	char	*s;

	s = ft_strdup(str[i]);
	free(str[i]);
	str[i] = ft_remove_squotes(s);
	free(s);
}

char	*get_expand(char *s)
{
	int		i;
	int		j;
	char	*str;
	int		len;
	int		k;

	i = ft_var(s);
	i++;
	j = ft_before_exp(s);
	if (s[j] == '$')
		j++;
	len = i - j;
	str = ft_calloc(sizeof(char), (len + 1));
	k = 0;
	while (j < i)
		str[k++] = s[j++];
	str[k] = '\0';
	if (is_a_quote(s))
	{
		free(str);
		return (NULL);
	}
	return (str);
}

int	quote_after_exp(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	while (s[i] && s[i] == '$')
		i++;
	if (s[i] && s[i] == '\"')
		return (1);
	if (s[i] && s[i] == ' ')
		return (1);
	if (s[i] && s[i] == '\0')
		return (1);
	return (0);
}
