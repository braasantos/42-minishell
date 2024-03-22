/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:03:47 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/21 13:03:49 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_pwd(t_mini *mini, int i)
{
	char	*env;

	if (!mini->args[i + 1])
	{
		env = getcwd(0, 0);
		ft_printf("%s\n", env);
		free(env);
		return (1);
	}
	else
		printf("Minishell: pwd with options\n");
	return (1);
}
