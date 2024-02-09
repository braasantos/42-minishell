#include "../inc/minishell.h"

void ft_exit(t_mini *mini)
{
	free(mini->args);
	free(mini->str);
	free(mini->newenvp);
	exit(1);
}
void check_all(t_mini *mini)
{
	if (mini->args == NULL)
		return;
	else if (ft_strcmp(mini->args[0], "exit") == 0)
		ft_exit(mini);
}
int count_pipes(t_mini *mini)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}
// void ft_close2(t_mini *mini)
// {
// 	dup2(mini->end[0], STDIN_FILENO);
// 	dup2(mini->end[1], STDOUT_FILENO);
// 	close(mini->end[1]);
// 	close(mini->end[0]);
// }

// void ft_close1(t_mini *mini)
// {
// 	dup2(mini->end[1], STDOUT_FILENO);
// 	close(mini->end[0]);
// 	close(mini->end[1]);
// }

// void first_c(t_mini *mini)
// {
// 	ft_child1(mini);
// }
void second_c(t_mini *mini)
{
	mini->child2 = fork();
	if (mini->child2 == 0)
	{
		// if (i == (count))
		ft_child2(mini);
	}
	else
	 	waitpid(-1, NULL, 0);
}
void ft_child1(t_mini *mini)
{
	dup2(mini->end[1], STDOUT_FILENO);
	close(mini->end[0]);
	if (execve(mini->cmd1[0], mini->args, mini->newenvp) == -1)
	{
		perror("execve");
        exit(EXIT_FAILURE);
	}
}

void ft_child2(t_mini *mini)
{
	dup2(mini->end[0], STDIN_FILENO);
	close(mini->end[1]);
	close(mini->end[0]);
	if (execve(mini->cmd1[2], mini->args, mini->newenvp) == -1)
	{
		perror("execve");
        exit(EXIT_FAILURE);
	}
}
int exec_pipes(t_mini *mini)
{
	int count;
	int i;

	count = count_pipes(mini);
	if (count == 0)
		return (0);
	else
	{
		i = 0;
		while (i < count)
		{
			if (pipe(mini->end) == -1)
				printf("error with pipes\n");
			mini->newpro = fork();
			if (mini->newpro == 0)
				ft_child1(mini);
			else
			{
				second_c(mini);
				waitpid(-1, NULL, 0);
			}
			i++;
		}
		return (1);
	}
}

void parsing(t_mini *mini)
{
	mini->args = ft_split(mini->str, ' ');
	check_all(mini);
	put_cmd(mini);
	if (exec_pipes(mini) == 1)
		return;
	if ((ft_strcmp(mini->args[0], "cd")) == 0 || (ft_strcmp(mini->args[0], "~") == 0))
		get_cd(mini->args[1], mini);
	mini->newpro = fork();
	if (mini->newpro == 0)
	{
		if (!mini->cmd1[0])
			print(COMMAND_NOT_FOUND, mini->cmd1[0]);
		if (execve(mini->cmd1[0], mini->args, mini->newenvp) == -1)
			ft_exit(mini);
	}
	else
		waitpid(-1, NULL, 0);
}
