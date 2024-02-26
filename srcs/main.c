#include "../inc/minishell.h"

int g_signal;

void ft_free_arr(char **str)
{
	int i;

	if (!str)
		return;
	i = -1;
	while (str[++i])
	{
		if (str[i])
			free(str[i]);
	}
	free(str);
	str = NULL;
}
static void init_all(t_mini *mini)
{
	mini->newenvp = NULL;
	mini->args = NULL;
	mini->new_str = NULL;
	mini->fd1 = 0;
	mini->fd0 = 0;
	mini->STDIN = 0;
	mini->STDOUT = 1;;
	mini->exit_flag = 0;
}
int main(int ac, char **av)
{
	t_mini mini;
	extern char **environ;
	char *str;

	init_all(&mini);
	mini.newenvp = get_newenvp(environ);
	if (ac >= 2 && av)
		return (ft_printf("pls do not use arguments :(\n"));
	ft_init_signals();
	while (1)
	{
		str = readline("\033[0;34mminishell \033[0m");

		mini.new_str = pad_central(str);
		mini.args = ft_split(mini.new_str, ' ');
		if (!mini.args)
			break;
		add_history(str);
		parsing(&mini, str);
		// ft_free_arr(mini.newenvp);
		free(str);
	}
}
