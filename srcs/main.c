/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:27:03 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/10 14:13:08 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_signal;

static void init_all(t_mini *mini)
{
	g_signal = 0;
	mini->newenvp = NULL;
	mini->another_split = NULL;
	mini->path_to_cmd = NULL;
	mini->exec_args = NULL;
	mini->args = NULL;
	mini->new_str = NULL;
	mini->before = NULL;
	mini->after = NULL;
	mini->echo_split = NULL;
	mini->fd1 = 0;
	mini->fd0 = 0;
	mini->stdin_fd = 0;
	mini->stdout_fd = 1;
	mini->exit_flag = 0;
	mini->echo_flag = 0;
	mini->flag_echo = 0;
	mini->free_flag = 0;
	mini->st_din = 0;
	mini->st_dout = 1;
}

char	*ft_strncpy(char* destination, const char* source, size_t num)
{
	size_t i;

	i = 0;
	while (i < num && source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}

void init_split(t_split *split, char *str)
{
	int len;

	split->i = 0;
	split->start = 0;
	split->words = 0;
	split->temp = ft_split(str, ' ');
	len = export_len(split->temp);
	ft_free_arr(split->temp);
	split->quotes = false;
	split->s = (char **)malloc((len + 1) * sizeof(char *));
}

char **return_split(t_split *split, char *str)
{
	split->tokens = split->i - split->start;
	if (split->tokens > 0)
	{
		split->s[split->words] = (char *)malloc((split->tokens + 1) * sizeof(char));
		ft_strncpy(split->s[split->words], &str[split->start], split->tokens);
		split->words++;
	}
	split->s[split->words] = NULL;
	return (split->s);
}

void	middle_split(t_split *split, char *str)
{
	if (count_dquotes(str) > 1)
	{
		if (str[split->i] == '\"')
			split->quotes = !split->quotes;
		else if (str[split->i] == ' ' && !split->quotes)
		{
			return_split(split, str);
			split->start = split->i + 1;
		}
	}
	if (count_squotes(str) > 1)
	{
		if (str[split->i] == '\'')
			split->quotes = !split->quotes;
		else if (str[split->i] == ' ' && !split->quotes)
		{
			return_split(split, str);
			split->start = split->i + 1;
		}
	}
}
char **new_split(char *str)
{
	t_split split;

	init_split(&split, str);
	while (str[split.i])
	{
		if (count_quotes(str) > 0)
			middle_split(&split, str);
		else
		{
			if (str[split.i] == ' ')
			{
				return_split(&split, str);
				split.start = split.i + 1;
			}
		}
		split.i++;
	}
	return (return_split(&split, str));
}

int main(int ac, char **av)
{
	t_mini mini;
	extern char **environ;

	if (ac >= 2 && av)
		return (ft_putstr_fd("pls do not use arguments :(\n", 2), 0);
	init_all(&mini);
	mini.newenvp = get_newenvp(environ);
	parser(&mini);
}

void parser(t_mini *mini)
{
	while (1)
	{
		signals(1, mini);
		mini->str = readline("\001\033[0;34m\002minishell \001\033[0m\002");
		if (!mini->str)
			signals(3, mini);
		mini->new_str = pad_central(mini->str);
		mini->args = new_split(mini->new_str);
		while_loop(mini->args);
		check_comand(mini);
		if (!mini->args[0])
		{
			free_struct(mini);
			continue ;
		}
		add_history(mini->str);
		parsing(mini, mini->new_str);
		free_struct(mini);
	}
}