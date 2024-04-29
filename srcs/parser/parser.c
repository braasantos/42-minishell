/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:28:37 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 11:31:28 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_mini *mini)
{
	while (1)
	{
		mini->str = readline("\001\033[0;34m\002minishell \001\033[0m\002");
		if (!mini->str)
			ft_handle_eof(mini);
		mini->new_str = add_space(mini->str);
		if (!check_spaces(mini->str))
			add_history(mini->str);
		if (checking(mini))
		{
			free(mini->str);
			free(mini->new_str);
			if (mini->args)
				ft_free_arr(mini->args);
			continue ;
		}
		if (execute(mini))
		{
			redirect(mini);
			free_struct(mini);
			continue ;
		}
		free_struct(mini);
	}
}

int	handle_tokens(t_mini *mini)
{
	char	**s;
	t_split	split;

	split.string = NULL;
	s = ft_newsplit(mini->new_str, split);
	ft_free_arr(split.string);
	if (pipe_check(s))
		return (ft_free_arr(s), 1);
	if (!s[0])
		return (ft_free_arr(s), 0);
	handle_quotes(s);
	check_comand(s, mini);
	if (change_args(mini, &s))
		return (ft_free_arr(s), 1);
	if (!s[0])
		return (ft_free_arr(s), 1);
	if (doredirect(&s, mini))
		return (1);
	mini->args = ft_arrcpy(s);
	ft_free_arr(s);
	update_pwd(mini);
	disp_pwd(mini);
	if (heredoc_first(mini))
		return (1);
	return (0);
}
