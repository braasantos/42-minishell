#include "../../inc/minishell.h"

int str_len(char **str)
{
	int i = 0;

	while (str[i] != NULL)
		i++;
	return (i);
}

int have_redirect(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], ">") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], "<") == 0)
			return (2);
		i++;
	}
	return (0);
}

int builtins(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "exit"))
	{
		mini->exit_flag = 1;
		free_struct_2(mini);
	}
	if (!ft_strcmp(mini->args[0], "echo"))
		return (echo_cmd(mini->args));
	if ((!ft_strcmp(mini->args[0], "cd")) || (!ft_strcmp(mini->args[0], "~")))
		return (get_cd(mini));
	return (0);
}

int	check_parser2(t_mini *mini, int i)
{
	int file_fd;

	file_fd = 0;
	if (is_a_option(mini->args[i], mini))
	{
		file_fd = open(mini->args[i], O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (!file_fd)
		{
			ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
			return (1);
		}
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s'\n", mini->args[i]);
		return (1);
	}
	return (0);
}
int	check_parser(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
		{
			if (mini->args[i + 1])
			{
				if (check_parser2(mini, (i + 1)) == 1)
					return (1);
			}
			else
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		if (!ft_strcmp(mini->args[i], "<"))
			if (check_parser3(mini, i) == 1)
				return (1);
		i++;
	}
	return (0);
}
int	check_parser3(t_mini *mini, int i)
{
	if (mini->args[i + 1])
	{
		if (!ft_strcmp(mini->args[i +1], ">"))
			return (0);
		if (is_a_file(mini->args[i + 1]))
			return (0);
		else
		{
			printf("minishell: %s: No such file or directory\n", mini->args[i + 1]);
			return (1);
		}
	}
	else
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}