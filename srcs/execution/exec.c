#include "../../inc/minishell.h"

void execute(t_mini *mini)
{
	int i;

	i = 0;
	if (is_a_cmd(mini->args[i], mini) == false)
	{
		print(COMMAND_NOT_FOUND, mini->args[i]);
		return;
	}
	while (mini->args[i])
	{
		// if (is_a_red(mini->args[i]))
		// printf("%d redirect\n", i);
		if (is_a_cmd(mini->args[i], mini))
			create_flow(mini, mini->args[i]);
		// if (is_a_file(mini->args[i]))
		// 	printf("%d file\n", i);
		// create_file(mini);
		// if (is_a_file_to_create(mini->args[i], mini))
		// 	printf("%d file to create\n", i);
		i++;
		mini->flag = 1;
		// close(mini->end[0]);
		// close(mini->end[1]);
	}
}

void first_pipe(t_mini *mini, char *s)
{
	pid_t newpro;

	newpro = fork();
	if (newpro < 0)
		exit(1);
	if (newpro == 0)
		firs_pipe(mini, s);
	else
		waitpid(-1, NULL, 0);
}

void second_pipe(t_mini *mini)
{
	int count;
	pid_t newpro;

	count = count_pipes(mini);
	newpro = fork();
	if (newpro < 0)
		exit(1);
	if (newpro != 0)
	{
		if (count == 1)
		{
			close_final(mini);
			ft_child2(mini);
		}
		// else
		// middle_pipe(mini);
	}
	else
		waitpid(-1, NULL, 0);
	mini->flag = 0;
}

void for_loop(char **s)
{
	for (int i = 0; s[i]; i++)
		ft_printf("%s\n", s[i]);
}

void create_flow(t_mini *mini, char *s)
{
	update_path(mini, s);
	if ((count_pipes(mini) == 0) && (have_redirect(mini) == 0))
		create_child(mini, s);
	else if (count_pipes(mini) > 0)
	{
		if (mini->flag == 0)
			if (pipe(mini->end) == -1)
			{
				printf("error with pipe\n");
				ft_exit(mini);
			}
		if (mini->flag == 0 && (check_position(mini, s) == 0))
			first_pipe(mini, s);
		if (mini->flag == 1)
			second_pipe(mini);
	}
	delete_path(mini);
}
