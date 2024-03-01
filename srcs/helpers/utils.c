#include "../../inc/minishell.h"

void	pad(char *src, char *dest, int i, int j)
{
	char	skip;

	while (src[i])
	{
		if (src[i] && find_char(src[i], "|><") && !quotes_open(src, i))
		{
			dest[j++] = ' ';
			skip = src[i];
			while (src[i] == skip)
				dest[j++] = src[i++];
			dest[j++] = ' ';
			continue ;
		}
		dest[j++] = src[i];
		i++;
	}
}

int check_inutils(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "<") || !ft_strcmp(mini->args[0], ">"))
		return (ft_printf("Minishell: syntax error near unexpected token `newline'\n"), 1);
	return (0);
}

int	find_char(char c, char *find)
{
	int	i;

	i = -1;
	while (find[++i])
		if (find[i] == c)
			return (1);
	return (0);
}

int	padding_needed(char *str, int i, int pad)
{
	char	skip;

	while (str[i])
	{
		if (str[i] && find_char(str[i], "|><") && !quotes_open(str, i))
		{
			skip = str[i];
			while (str[i] && str[i] == skip)
				i++;
			pad += 2;
			continue ;
		}
		i++;
	}
	return (pad);
}

char	*pad_central(char *str)
{
	int		extra;
	char	*ret;

	extra = padding_needed(str, 0, 0);
	if (extra == 0)
		return (ft_strdup(str));
	ret = (char *)ft_calloc(1, ft_strlen(str) + extra + 1);
	pad(str, ret, 0, 0);
	return (ret);
}

int	quotes_open(char *str, int target_index)
{
	int		open;
	char	wanted_quote;
	int		i;

	open = 0;
	i = 0;
	wanted_quote = -1;
	while (str[i])
	{
		if (find_char(str[i], "\"\'") && !open)
		{
			open = 1;
			wanted_quote = str[i++];
		}
		if (str[i] && open && str[i] == wanted_quote)
			open = 0;
		if (i == target_index)
			return (open);
		i++;
	}
	return (0);
}

int	pipe_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && !quotes_open(str, i))
		{
			if (i == 0)
				return (0);
			if (str[i + 1] == '\0')
				return (0);
			if (i != 0 && (str[i - 1] == '|' || str[i + 1] == '|'))
				return (0);
		}
	}
	return (1);
}

int	redirect_basic_check(char *str)
{
	int	i;
	int	count;

	i = -1;
	while (str[++i])
	{
		count = 0;
		if (find_char(str[i], "><") && !quotes_open(str, i))
		{
			while (str[i] && find_char(str[i], "><"))
			{
				if (find_char(str[i + 1], "><") && str[i + 1] != str[i])
					return (0);
				count++;
				i++;
			}
		}
		if (count > 2)
			return (0);
	}
	return (1);
}

int ft_check_open_quotes(char *str)
{
	char quote;
	int state;

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

int count_pipes(t_mini *mini)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

void print(t_op op, char *ag)
{
	if (op == COMMAND_NOT_FOUND)
		ft_printf("%s: command not found\n", ag);
}

int check_args(char *str)
{
	int i;
	int j;

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

int ft_strcmp(char *str1, char *str2)
{
	int i;

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