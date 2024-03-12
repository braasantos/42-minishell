#include "../inc/minishell.h"

int g_signal;

static void init_all(t_mini *mini)
{
	g_signal = 0;
	mini->newenvp = NULL;
	mini->args = NULL;
	mini->new_str = NULL;
	mini->before = NULL;
	mini->after = NULL;
	mini->fd1 = 0;
	mini->fd0 = 0;
	mini->STDIN = 0;
	mini->STDOUT = 1;
	mini->stdin_fd = 0;
	mini->stdout_fd = 1;
	mini->exit_flag = 0;
	mini->echo_flag = 0;
	mini->STDIN = STDIN_FILENO;
	mini->STDOUT = STDOUT_FILENO;
	mini->interact = false;
}


int main(int ac, char **av)
{
	t_mini mini;
	extern char **environ;

	if (ac >= 2 && av)
		return (ft_printf("pls do not use arguments :(\n"));
	init_all(&mini);
	mini.newenvp = get_newenvp(environ);
	signals_start();
	exec_signals(0, &mini);
	parser(&mini);
}
void parser(t_mini *mini)
{
	while (1)
	{
		mini->interact = true;
		mini->str = readline("\033[0;34mminishell \033[0m");
		mini->interact = false;
		mini->new_str = pad_central(mini->str);
		mini->args = which_split(mini->new_str, mini);
		check_comand(mini);
		if (!mini->new_str)
		{
			free_struct(mini);
			free(mini->new_str);
			exit(1);
		}
		if (!mini->args[0])
		{
			free_struct(mini);
			continue;
		}
		add_history(mini->str);
		parsing(mini, mini->new_str);
		free_struct(mini);
	}
}
