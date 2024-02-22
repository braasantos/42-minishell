#include "../inc/minishell.h"

int g_signal;

void	ft_free_arr(char **str)
{
	int i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		free(str[i]);
	}
	free(str);
	str = NULL;
}
void	init_all(t_mini *mini)
{
	mini->cmd = NULL;
	mini->newenvp = NULL;
	mini->args= NULL;
	mini->new_str = NULL;
	mini->fd1 = 0;
	mini->fd0 = 0;
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
		// new_string(str, &mini);
		// free(str);
		if (str[0])
		{
			add_history(str);
			parsing(&mini, str);
		}
		free(str);
	}
}
