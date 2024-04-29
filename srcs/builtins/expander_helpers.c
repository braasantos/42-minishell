/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:23:39 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:23:40 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_before_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

char	*ft_before(char *s)
{
	int		i;
	char	*before_quo;
	char	*space;
	int		j;

	i = ft_before_exp(s);
	if (i == 0)
	{
		space = ft_calloc(1, sizeof(char));
		space[0] = '\0';
		return (space);
	}
	before_quo = ft_calloc(sizeof(char), (i + 1));
	if (before_quo == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		before_quo[j] = s[j];
		j++;
	}
	before_quo[j] = '\0';
	return (before_quo);
}

int	ft_isspecial(char c)
{
	if (ft_isdigit(c) == 1)
		return (1);
	if (ft_isalpha(c) == 1)
		return (1);
	return (0);
}
/* 
    RETURN THE POSITION OF THE 
    LAST ELEMENT OF THE VAR TO EXPAND
 */

int	ft_var(char *str)
{
	int	i;

	i = ft_before_exp(str);
	if (str[i] && str[i] == '$')
		i++;
	if (str[i] && str[i] == '?')
		return (i);
	while (str[i])
	{
		if (str[i] == ' ' || !ft_isspecial(str[i]))
			break ;
		i++;
	}
	i--;
	return (i);
}

char	*ft_after(char *s)
{
	int		i;
	int		len;
	char	*after_quo;

	i = ft_var(s);
	len = ft_strlen(s) - i - 1;
	after_quo = ft_calloc(sizeof(char), (len + 1));
	ft_strncpy(after_quo, s + i + 1, len);
	return (after_quo);
}
