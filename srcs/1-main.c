#include "../inc/minishell.h"

int g_signal;

void print(t_op op, char *ag)
{
	if (op == COMMAND_NOT_FOUND)
		ft_printf("%s: command not found\n", ag);
}

void get_cd(char *args, t_mini *mini)
{
	char *home_dir;

	home_dir = getenv("HOME");
	if (args == NULL || ft_strcmp(args, "~") == 0)
		chdir(home_dir);
	else if (args[0] == '$')
		chdir(getenv(args + 1));
	else if (chdir(args))
	{
		printf("error with cd\n");
		ft_exit(mini);
	}
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
void	init_all(t_mini *mini)
{
	mini->cmd = NULL;
	mini->wrongarg = NULL;
	mini->newenvp = NULL;
	mini->args= NULL;
	mini->str = NULL;
}
int main(int ac, char **av)
{
	t_mini mini;
	// char *str;
	extern char **environ;

	init_all(&mini);
	mini.newenvp = get_newenvp(environ);
	if (ac >= 2 && av)
		return (ft_printf("pls do not use arguments :(\n"));
	while (1)
	{
		mini.str = readline("\033[0;34mminishell \033[0m");
		if (mini.str[0])
		{
			add_history(mini.str);
			parsing(&mini);
		}
		free(mini.str);
	}
}
