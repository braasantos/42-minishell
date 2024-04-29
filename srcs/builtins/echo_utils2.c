/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:25:37 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:25:38 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**new_args(char **s, int k, int k1)
{
	char	**newenvp;
	int		i;
	int		j;
	int		len;
	int		new_index;

	len = arr_len(s);
	newenvp = ft_calloc((len + 1), sizeof(char *));
	i = 0;
	new_index = 0;
	while (i < len)
	{
		if (i != k && i != k1)
		{
			j = ft_strlen(s[i]);
			newenvp[new_index] = ft_calloc((j + 1), sizeof(char));
			if (newenvp[new_index] == NULL)
				return (free(newenvp), NULL);
			ft_strcpy(newenvp[new_index], s[i]);
			new_index++;
		}
		i++;
	}
	newenvp[new_index] = NULL;
	return (newenvp);
}

int	have_redi(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0)
			return (1);
		if (ft_strcmp(s[i], "<") == 0)
			return (1);
		if (ft_strcmp(s[i], ">>") == 0)
			return (1);
		if (ft_strcmp(s[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	redirect_output(char *s)
{
	int		file_fd;
	char	*str;

	if (!s)
		return (1);
	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (is_a_file(str))
	{
		if (access(str, W_OK) == -1)
			return (free(str), 1);
	}
	file_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file_fd == -1)
		return (free(str), 1);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (free(str), 0);
}

int	redirect_input(char *s)
{
	int		file_fd;
	char	*str;

	if (!s)
		return (1);
	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (is_a_file(str))
	{
		if (access(s, W_OK) == -1)
			return (free(str), 1);
	}
	file_fd = open(str, O_RDONLY);
	if (file_fd == -1)
		return (free(str), 1);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (free(str), 0);
}

int	deal_append(char *s, char *ss)
{
	if (!ft_strcmp(s, ">>"))
		if (handle_append(ss))
			return (1);
	return (0);
}
