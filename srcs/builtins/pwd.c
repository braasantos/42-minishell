/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:24:06 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:24:07 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd(t_mini *mini)
{
	int	i;

	if (mini->pwd)
	{
		free(mini->pwd);
		mini->pwd = NULL;
	}
	i = -1;
	if (check_env(mini))
	{
		mini->pwd = getcwd(0, 0);
		return ;
	}
	while (mini->envp[++i])
	{
		if (!ft_strncmp(mini->envp[i], "PWD", 3))
			mini->pwd = export_key(mini->envp[i]);
	}
	if (!mini->pwd)
	{
		mini->pwd = getcwd(0, 0);
		return ;
	}
}

void	do_shlvl(t_mini *mini)
{
	int		i;
	char	*key;
	char	*value_env;
	int		value;
	char	*number;

	i = -1;
	if (!mini->envp)
		return ;
	while (mini->envp[++i])
	{
		if (!ft_strncmp(mini->envp[i], "SHLVL", 5))
		{
			value_env = export_key(mini->envp[i]);
			value = ft_atoi(value_env);
			value++;
			key = export_var(mini->envp[i]);
			free(mini->envp[i]);
			number = ft_itoa(value);
			mini->envp[i] = ft_strjoin(key, number);
			free(key);
			free(value_env);
			free(number);
		}
	}
}

int	print_pwd(t_mini *mini)
{
	ft_printf("%s\n", mini->pwd);
	return (1);
}

void	disp_pwd(t_mini *mini)
{
	int		i;
	char	**s;
	char	*pwd;

	i = 0;
	if (check_env(mini))
		return ;
	s = ft_arrcpy(mini->args);
	pwd = get_env("HOME", mini);
	while (s[i])
	{
		if (!ft_strcmp(s[i], "~"))
		{
			free(mini->args[i]);
			mini->args[i] = ft_strdup(pwd);
		}
		i++;
	}
	ft_free_arr(s);
	s = NULL;
}
