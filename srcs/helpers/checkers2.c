/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:49:58 by gabe              #+#    #+#             */
/*   Updated: 2024/04/18 20:50:16 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_cmd(t_mini *mini, int i)
{
	struct stat	stats;

	stat(mini->args[i], &stats);
	if (ft_strchr(mini->args[i], '/') && stat(mini->args[i], &stats))
		print(NO_SUCH_FILE_OR_DIR, mini->args[i]);
	else if (access(mini->args[i], F_OK))
		print(COMMAND_NOT_FOUND, mini->args[i]);
	else if (access(mini->args[i], F_OK | X_OK)
		&& ft_strchr(mini->args[i], '/'))
		print(NO_PERMISSION, mini->args[i]);
	else if (S_ISDIR(stats.st_mode) && ft_strchr(mini->args[i], '/'))
		print(IS_DIR, mini->args[i]);
	else if (S_ISDIR(stats.st_mode))
		print(COMMAND_NOT_FOUND, mini->args[i]);
	else if (is_a_cmd(mini->args[i], mini) == false
		&& is_a_builtin(mini, i) == false)
		print(COMMAND_NOT_FOUND, mini->args[i]);
}

bool	is_not_a_cmd(char *s)
{
	if (is_a_pipe(s, 0) && count_quotes(s) > 0)
		return (true);
	if (is_a_pipe(s, 0) || is_a_red(s) || ft_strstartswith(s, "-")
		|| count_quotes(s) > 0 || is_a_append_here(s)
		|| is_a_file(s) || is_a_number(s))
		return (false);
	return (true);
}

int	have_redirect(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], ">") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], "<") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], ">>") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}
