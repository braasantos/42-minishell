#include "../../inc/minishell.h"

void	print_arg(char *str, int total, int current, int flag)
{
	int	i = 0;

	while(str[i])
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
	int 	flag_nl = 1;
	int 	option = 1;
	int 	i = 1;
	int		argcnt = 1;

	while (tokens[argcnt])
		argcnt++;
	while (tokens[i])
	{
		if (ft_check_echo_arguments(tokens[i]) && option)
		{
			flag_nl = 0;
			i++;
		}
		else
			option = 0;
		if (!option)
		{
			print_arg(tokens[i], argcnt, i, mini->echo_flag);
			i++;
		}
	}
	ft_print_new_line(flag_nl);
	return (1);
}

int ft_check_echo_arguments(char *array_args)
{
	int i = 0;
	if (array_args[i] != '-')
		return 0;
	i++;
	if (array_args[i] != 'n')
		return 0;
	while (array_args[i] == 'n')
		i++;
	return (array_args[i] == '\0');
}


void ft_print_new_line(int flag_nl)
{
	if (flag_nl)
		printf("\n");
}
