/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:22:05 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:22:07 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
