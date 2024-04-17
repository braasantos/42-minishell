/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:51:59 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/17 13:42:24 by bjorge-m         ###   ########.fr       */
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
	if (is_a_quote(var))
		return (NULL);
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
		return (ft_fprintf(2, "Minishell: cd: HOME not set\n"), 1);
	return (0);
}

void	update_envs(char *cwd, t_mini *mini)
{
	char	*env;

	set_env_var("OLDPWD", cwd, mini);
	env = getcwd(0, 0);
	set_env_var("PWD", env, mini);
	free(env);
	update_pwd(mini);
}

void	change_dir(char *path, t_mini *mini)
{
	char	*cwd;
	char	buff[4097];

	if (chech_path(path))
		return ;
	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		if (check_env(mini))
			return ;
		update_envs(cwd, mini);
	}
	else
	{
		if (access(path, F_OK) == -1)
		{
			g_signal = 1;
			ft_fprintf(2, " No such file or directory\n");
		}
		else if (access(path, R_OK) == -1)
			ft_fprintf(2, " permission denied: \n");
		else
			ft_fprintf(2, " not a directory: \n");
	}
}
