/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:19:23 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/12 15:06:50 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_add(t_mini *mini, char *ag)
{
	char	*cmd1;
	char	**str;
	char	*tmp;
	int		i;

	tmp = NULL;
	cmd1 = NULL;
	str = get_path(mini->newenvp);
	if (access(ag, X_OK) == 0)
		return (ft_free_arr(str), ft_strdup(ag));
	if (!str || !*str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		cmd1 = ft_strjoin(tmp, ag);
		free(tmp);
		if (access(cmd1, X_OK) == 0)
			return (ft_free_arr(str), cmd1);
		free(cmd1);
		i++;
	}
	return (ft_free_arr(str), NULL);
}

char	**get_path(char **newenv)
{
	int		i;
	char	*str;
	char	**newstr;

	i = 0;
	newstr = NULL;
	str = NULL;
	if (!newenv)
		return (NULL);
	while (newenv[i])
	{
		if (!ft_strncmp(newenv[i], "PATH=", 5))
			str = ft_substr(newenv[i], 5, ft_strlen(newenv[i]));
		i++;
	}
	if (str)
	{
		newstr = ft_split(str, ':');
		free(str);
	}
	return (newstr);
}

char	**get_newenvp(char **envp)
{
	char	**newenvp;
	int		i;
	int		j;
	int		len;

	len = str_len(envp);
	newenvp = (char **)malloc((len + 1) * sizeof(char *));
	if (!newenvp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		j = ft_strlen(envp[i]);
		newenvp[i] = (char *)malloc((j + 1) * sizeof(char));
		if (!newenvp[i])
		{
			ft_free_arr(newenvp);
			return (NULL);
		}
		ft_strcpy(newenvp[i], envp[i]);
		i++;
	}
	newenvp[i] = NULL;
	return (newenvp);
}

bool	is_a_append_here(char *s)
{
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (true);
	return (false);
}

bool	is_a_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			return (true);
		i++;
	}
	return (false);
}
