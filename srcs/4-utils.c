#include "../inc/minishell.h"


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