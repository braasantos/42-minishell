#include "../inc/minishell.h"

int echo_cmd(char **tokens)
{
	int flag_nl = 1;
	int option = 1;
	int i = 0;

	while (tokens[i])
	{
		if (ft_check_echo_arguments(tokens[i]) && option)
		{
			flag_nl = 0;
			i++;
		}
		else
		{
			option = 0;
		}
		if (!option)
		{
			printf("%s", tokens[i]);
			ft_print_echo_space(&tokens[i]);
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
	return array_args[i] == '\0';
}

void ft_print_echo_space(char **aux)
{
	if (*(aux + 1))
		printf(" ");
}

void ft_print_new_line(int flag_nl)
{
	if (flag_nl)
		printf("\n");
}
