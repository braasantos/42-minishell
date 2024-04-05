/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:08:45 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/05 21:30:09 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	twenty_six_lines(t_mini *mini)
{
	close_pipes(mini);
	get_exit_status(mini);
}

char	*export_var(char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	str = malloc(sizeof(char) * i + 2);
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != '=')
			str[i] = s[i];
		else
			break ;
		i++;
	}
	if ( s[i] == '=')
	{
		str[i] = '=';
		str[i + 1] = '\0';
	}
	else
		str[i] = '\0';
	return (str);
}

int	export_key_util(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
		i++;
	while (s[i])
	{
		j++;
		i++;
	}
	return (j);
}

char	*export_key(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = export_key_util(s);
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
		i++;
	j = 0;
	while (s[i])
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	get_qmark(t_mini *mini, int i)
{
	int		j;
	char	*before;
	char	*after;
	char	*temp;

	j = 0;
	while (mini->args[i])
	{
		if (mini->args[i][j] == '?')
		{
			free(mini->args[i]);
			temp = ft_itoa(g_signal);
			before = ft_strjoin(mini->before, temp);
			after = ft_strjoin(before, mini->after);
			mini->args[i] = ft_strdup(after);
			free(before);
			free(after);
			free(temp);
			return (1);
		}
		else
			j++;
	}
	return (0);
}
