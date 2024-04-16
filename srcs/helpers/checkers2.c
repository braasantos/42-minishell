/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabe <gabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:49:58 by gabe              #+#    #+#             */
/*   Updated: 2024/04/16 13:51:25 by gabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_a_option(char *s, t_mini *mini)
{
	char	*str;

	if (is_a_pipe(s) || is_a_red(s) || is_a_file(s))
		return (false);
	if (!ft_strcmp(s, "-"))
		return (true);
	str = ft_add(mini, s);
	if (access(str, X_OK) == -1)
		return (free(str), true);
	else
		return (free(str), false);
}
