#include "../../inc/minishell.h"

int	ft_check_open_quotes(char *str)
{
	char	quote;
	int		state;

	state = 0;
	while (*str)
	{
		if (!state && (*str == '\'' || *str == '\"'))
		{
			state = 1;
			quote = *str;
		}
		else if (state && *str == quote)
			state = 0;
		str++;
	}
	if (state && write(2, "Error: Open quotes\n", 19))
		return (0);
	return (1);
}

int	print(t_op op, char *ag)
{
	if (op == COMMAND_NOT_FOUND)
		ft_printf("%s: command not found\n", ag);
	return (1);
}

int	check_args(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			j++;
		i++;
	}
	if (j >= 1)
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}

bool	is_a_folder(char *s)
{
	if (access(s, F_OK) == -1)
		return (false);
	return (true);
}