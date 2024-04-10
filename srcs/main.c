/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:27:03 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/09 21:00:29 by braasantos       ###   ########.fr       */
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

char	*ft_strncpy(char* destination, char* source, size_t num)
{
	size_t i;

	i = 0;
	while (i < num && source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}
	while (i < num)
	{
		destination[i] = '\0';
		i++;
	}
	return (destination);
}

char	**parseString(char* str)
{
	int capacity = 20;
	char** tokens = (char**)malloc(capacity * sizeof(char*));
	int token_count = 0;
	bool in_quote = false;
	int token_start = 0;
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			in_quote = !in_quote;
		else if (str[i] == ' ' && !in_quote)
		{
			int token_length = i - token_start;
			if (token_length > 0)
			{
				tokens[token_count] = (char*)malloc((token_length + 1) * sizeof(char));
				ft_strncpy(tokens[token_count], &str[token_start], token_length);
				tokens[token_count][token_length] = '\0';
				++token_count;
				if (token_count >= capacity)
				{
					capacity *= 2;
					tokens = (char**)realloc(tokens, capacity * sizeof(char*));
				}
			}
			token_start = i + 1;
		}
		i++;
	}
	int token_length = i - token_start;
	if (token_length > 0)
	{
		tokens[token_count] = (char*)malloc((token_length + 1) * sizeof(char));
		ft_strncpy(tokens[token_count], &str[token_start], token_length);
		tokens[token_count][token_length] = '\0';
		++token_count;
	}
	tokens[token_count] = NULL;
	return (tokens);
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
		mini->args = parseString(mini->new_str);
		// while_loop(mini->args);
		check_comand(mini);
		// change_args(mini, 0);
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
