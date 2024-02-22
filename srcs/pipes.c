#include "../inc/minishell.h"

void middle_pipe(t_mini *mini)
{
	char **args = ft_split(mini->args[4], ' ');
	close(mini->end[1]);
	dup2(mini->end[0], STDIN_FILENO);
	close(mini->end[0]);
	dup2(mini->end[1], STDOUT_FILENO);
	close(mini->end[1]);
	if (!mini->cmd1[4])
		print(COMMAND_NOT_FOUND, mini->args[4]);
	if (execve(mini->cmd1[4], args, mini->newenvp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void second_c(t_mini *mini)
{
	pid_t child2;
	child2 = fork();
	if (child2 == 0)
		ft_child2(mini);
	else
		waitpid(-1, NULL, 0);
}
void ft_child1(t_mini *mini)
{
	char **args = ft_split(mini->args[0], ' ');

	if (!mini->cmd1[0])
		print(COMMAND_NOT_FOUND, mini->args[0]);
	if (execve(mini->cmd1[0], args, mini->newenvp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void ft_child2(t_mini *mini)
{
	char **args = ft_split(mini->args[2], ' ');
	close(mini->end[1]);
	dup2(mini->end[0], STDIN_FILENO);
	close(mini->end[0]);
	if (!mini->cmd1[2])
		print(COMMAND_NOT_FOUND, mini->args[2]);
	if (execve(mini->cmd1[2], args, mini->newenvp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
int pipes(t_mini *mini)
{
	mini->child1 = fork();
	if (mini->child1 == 0)
		ft_child1(mini);
	else
	{
		second_c(mini);
		waitpid(mini->child1, NULL, 0);
		waitpid(mini->child2, NULL, 0);
		;
	}
	close(mini->end[0]);
	close(mini->end[1]);
	return (1);
}

void execute_second(t_mini *mini)
{
	int count;
	int i;

	count = count_pipes(mini);
	if (count > 0)
	{
		while (i < count)
		{
			pipe(mini->end);
			red_pipes(mini, i);
			create_child(mini);
			// close_pipes(mini);
			i++;
		}
	}
}
void red_pipes(t_mini *mini, int i)
{
	if (i == 1)
	{
		close(mini->end[0]);
		dup2(mini->end[1], STDOUT_FILENO);
		close(mini->end[1]);
	}
}