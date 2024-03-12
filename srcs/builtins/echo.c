#include "../../inc/minishell.h"

void print_arg(char *str, t_mini *mini, int current, int flag)
{
	int i;
	int total;

	i = 0;
	total = str_len(mini->args);
	while (str[i])
	{
		if (str[i] != '"')
			write(1, &str[i], 1);
		i++;
	}
	if (flag == 0)
		if (total > current)
			write(1, " ", 1);
}


int echo_cmd(char **tokens, t_mini *mini)
{
	int flag_nl;
	int option;
	int i;

	i = 1;
	flag_nl = 1;
	option = 1;
	check_expand(mini);
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], "-n") && option)
		{
			flag_nl = 0;
			i++;
		}
		else
			option = 0;
		if (!option)
		{
			print_arg(tokens[i], mini, i, mini->echo_flag);
			i++;
		}
	}
	return (ft_print_new_line(flag_nl), 1);
}

void ft_print_new_line(int flag_nl)
{
	if (flag_nl)
		ft_printf("\n");
}
