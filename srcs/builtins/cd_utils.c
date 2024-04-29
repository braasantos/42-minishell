/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:22:48 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:22:49 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_cdm(t_mini *mini)
{
	int		i;
	char	*home_dir;

	home_dir = get_env("OLDPWD", mini);
	if (!home_dir)
	{
		ft_fprintf(2, "Minishell: OLDPWD not set\n");
		return ;
	}
	i = -1;
	if (mini->pwd)
	{
		free(mini->pwd);
		mini->pwd = NULL;
	}
	while (mini->envp[++i])
	{
		if (!ft_strncmp(mini->envp[i], "OLDPWD", 6))
			mini->pwd = export_key(mini->envp[i]);
	}
	print_pwd(mini);
	change_dir(home_dir, mini);
	update_pwd(mini);
}

static int	has_two_args(char **args, t_mini *mini)
{
	if (args[1])
	{
		if (args[2])
		{
			ft_fprintf(2, "cd: too many arguments\n");
			g_signal = 1;
			return (1);
		}
		if (!ft_strcmp(args[1], "-"))
			handle_cdm(mini);
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
		update_pwd(mini);
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
	if (s[i] == '=')
	{
		str[i] = '=';
		str[i + 1] = '\0';
	}
	else
		str[i] = '\0';
	return (str);
}
