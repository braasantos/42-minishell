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

void free_struct(t_mini *mini)
{
	if (mini->args)
		ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
}

void free_struct_2(t_mini *mini)
{
	if (mini->args)
		ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	exit(1);
}
static void init_all(t_mini *mini)
{
	mini->newenvp = NULL;
	mini->args = NULL;
	mini->new_str = NULL;
	mini->fd1 = 0;
	mini->fd0 = 0;
	mini->STDIN = 0;
	mini->STDOUT = 1;
	mini->stdin_fd = 0;
	mini->stdout_fd = 1;
	mini->exit_flag = 0;
}


int main(int ac, char **av)
{
	t_mini mini;
	extern char **environ;

	init_all(&mini);
	mini.newenvp = get_newenvp(environ);
	if (ac >= 2 && av)
		return (ft_printf("pls do not use arguments :(\n"));
	ft_init_signals();
	while (1)
	{
		mini.str = readline("\033[0;34mminishell \033[0m");
		mini.new_str = pad_central(mini.str);
		mini.args = ft_split(mini.new_str, ' ');
		if (!mini.str)
		{
			free_struct(&mini);
			free(mini.str);
			exit(1);
		}
		if (!mini.args[0])
			continue;
		add_history(mini.str);
		parsing(&mini, mini.str);
		free_struct(&mini);
	}
}
