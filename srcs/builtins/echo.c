#include "../../inc/minishell.h"

<<<<<<< HEAD
void print_arg(char *str, int total, int current)
=======
void	print_arg(char *str, int total, int current, int flag)
>>>>>>> refs/remotes/origin/master
{
	int i;

	i = 0;
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

<<<<<<< HEAD
int echo_cmd(t_mini *mini)
=======
int echo_cmd(char **tokens, t_mini *mini)
>>>>>>> refs/remotes/origin/master
{
	int flag_nl;
	int option;
	int i;
	int argcnt;

	i = 1;
	argcnt = str_len(mini->args);
	flag_nl = 1;
	option = 1;
	check_expand(mini);
	while (mini->args[i])
	{
		if (ft_check_echo_arguments(mini->args[i]) && option)
		{
			flag_nl = 0;
			i++;
		}
		else
			option = 0;
		if (!option)
		{
<<<<<<< HEAD
			print_arg(mini->args[i], argcnt, i);
=======
			print_arg(tokens[i], argcnt, i, mini->echo_flag);
>>>>>>> refs/remotes/origin/master
			i++;
		}
	}
	return (ft_print_new_line(flag_nl), 1);
}

int ft_check_echo_arguments(char *args)
{
	int i;

	i = 0;
	if (args[i] != '-')
		return 0;
	i++;
	if (args[i] != 'n')
		return 0;
	while (args[i] == 'n')
		i++;
	return (args[i] == '\0');
}

<<<<<<< HEAD
void ft_print_echo_space(char **aux)
{
	if (*(aux + 1))
	{
		// printf("-%s-", *(aux + 1));
		printf(" ");
	}
}
=======
>>>>>>> refs/remotes/origin/master

void ft_print_new_line(int flag_nl)
{
	if (flag_nl)
		printf("\n");
}

