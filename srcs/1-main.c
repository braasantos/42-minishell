#include "../inc/minishell.h"

void	print(t_op op, char *ag)
{
	if (op == COMMAND_NOT_FOUND)
		printf("%s: command not found\n", ag);
}

void	get_cd(char *args)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (args == NULL)
		chdir(home_dir);
	else
		if(chdir(args))
			printf("error with cd\n");
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


int	main(int ac, char **av)
{
	t_mini	mini;
	char	*str;
	extern char **environ;

	mini.newenvp = get_newenvp(environ);
	if (ac >= 2 && av)
		return (ft_printf("pls do not use arguments :(\n"));
	while (1)
	{
		str = readline("\033[0;34mminishell \033[0m");
		if (str[0])
		{
			add_history(str);
			parsing(&mini, str);
		}
		free(str);
	}
}
