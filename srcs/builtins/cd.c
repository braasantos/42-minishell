/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:51:59 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/04 08:42:14 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env(char *var, t_mini *mini)
{
	int		i;
	char	*tmp;
	char	*str;

	i = -1;
	if (!var)
		return (NULL);
	str = ft_remove_quotes(var);
	tmp = ft_strjoin(str, "=");
	free(str);
	if (check_env(mini))
		return (NULL);
	while (mini->newenvp[++i])
	{
		if (ft_strstartswith(mini->newenvp[i], tmp))
		{
			free(tmp);
			return (ft_strchr(mini->newenvp[i], '=') + 1);
		}
	}
	free(tmp);
	return (NULL);
}

int	check_env(t_mini *mini)
{
	if (!mini->newenvp)
		return (1);
	return (0);
}

int	chech_path(char *s)
{
	if (!s)
		return (ft_putendl_fd("Minishell: cd: HOME not set", 2), 1);
	return (0);
}

void	change_dir(char *path, t_mini *mini)
{
	char	*cwd;
	char	buff[4097];
	char	*env;

	if (chech_path(path))
		return ;
	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		if (check_env(mini))
			return ;
		set_env_var("OLDPWD", cwd, mini);
		env = getcwd(0, 0);
		set_env_var("PWD", env, mini);
		free(env);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		if (access(path, F_OK) == -1)
			ft_putendl_fd("no such file or directory: ", 2);
		else if (access(path, R_OK) == -1)
			ft_putendl_fd("permission denied: ", 2);
		else
			ft_putendl_fd("not a directory: ", 2);
		write(2, path, 1);
	}
}

static int	has_two_args(char **args, t_mini *mini)
{
	if (args[1])
	{
		if (args[2])
		{
			ft_putendl_fd("cd: too many arguments", 2);
			return (1);
		}
		if (!ft_strcmp(args[1], "-"))
			print_pwd(mini, 0);
		else
			change_dir(args[1], mini);
		return (1);
	}
	return (0);
}

int	get_cd(t_mini *mini, int i)
{
	char	*home_dir;

	home_dir = get_env("HOME", mini);
	if ((!mini->args[i + 1]))
	{
		change_dir(home_dir, mini);
		return (1);
	}
	else
	{
		if (is_a_pipe(mini->args[i + 1]) || is_a_red(mini->args[i + 1])
			|| is_a_append_here(mini->args[i + 1]))
			return (1);
		if (has_two_args(mini->args, mini))
			return (1);
	}
	return (0);
}

int	ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}
