/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:26:50 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:26:51 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_arrcpy(char **envp)
{
	char	**newenvp;
	int		i;
	int		j;
	int		len;

	newenvp = NULL;
	len = arr_len(envp);
	newenvp = ft_calloc((len + 1), sizeof(char *));
	i = 0;
	while (i < len)
	{
		j = ft_strlen(envp[i]);
		newenvp[i] = ft_calloc((j + 1), sizeof(char));
		if (!newenvp[i])
		{
			ft_free_arr(newenvp);
			return (NULL);
		}
		ft_strcpy(newenvp[i], envp[i]);
		i++;
	}
	return (newenvp[i] = NULL, newenvp);
}

static char	**get_path(char **newenv)
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

char	*ft_add(t_mini *mini, char *ag)
{
	char	*cmd1;
	char	**str;
	char	*tmp;
	int		i;

	tmp = NULL;
	cmd1 = NULL;
	str = get_path(mini->envp);
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

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1[i] || !str2[i])
		return (1);
	while (str1[i] || str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
