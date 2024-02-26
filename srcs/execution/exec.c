#include "../../inc/minishell.h"

void execute(t_mini *mini)
{
	int n_pipes;

	n_pipes = count_pipes(mini);
	if (builtins(mini) == 1)
		return;
	if ((n_pipes == 0))
	{
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_child(mini, 0, 0, 0);
		free(mini->newpro);
	}
	else if ((n_pipes > 0))
	{
		mini->newpro = malloc(sizeof(int) * (n_pipes + 1));
		create_flow(mini);
		free(mini->newpro);
	}
}

void for_loop(char **s)
{
	for (int i = 0; s[i]; i++)
		ft_printf("%s\n", s[i]);
}
int pipe_creation(t_mini *mini)
{
	int i;
	int n_pipes;

	n_pipes = count_pipes(mini);
	mini->pipes_fd = malloc(sizeof(int) * (n_pipes * 2));
	i = 0;
	while (i < n_pipes)
	{
		if (pipe(mini->pipes_fd + (2 * i)) < 0)
		{
			ft_putstr_fd("Error while creating pipes", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void close_pipes(t_mini *mini)
{
	int i;
	int n_pipes;

	i = 0;
	n_pipes = count_pipes(mini);
	while (i < n_pipes * 2)
	{
		close(mini->pipes_fd[i]);
		i++;
	}
	free(mini->pipes_fd);
}

void create_flow(t_mini *mini)
{
	int i;
	int j;

	mini->STDIN = STDIN_FILENO;
	mini->STDOUT = STDOUT_FILENO;
	i = 0;
	j = 0;
	pipe_creation(mini);
	while (mini->args[i])
	{
		if (is_a_cmd(mini->args[i], mini))
		{
			create_child(mini, i, 1, j);
			j++;
		}
		i++;
	}
	close_pipes(mini);
	get_exit_status(mini);
}
