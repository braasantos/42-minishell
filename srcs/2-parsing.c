#include "../inc/minishell.h"

void ft_exit(t_mini *mini)
{
	free(mini->args);
	free(mini->str);
	free(mini->newenvp);
	exit(1);
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
void middle_pipe(t_mini *mini)
{
	char **args = ft_split(mini->args[4], ' ');
	close(mini->end[1]);			   // Close write end of the previous pipe
	dup2(mini->end[0], STDIN_FILENO);  // Redirect stdin to the read end of the previous pipe
	close(mini->end[0]);			   // Close duplicated read end of the previous pipe
	dup2(mini->end[1], STDOUT_FILENO); // Redirect stdout to the write end of the current pipe
	close(mini->end[1]);
	if (!mini->cmd1[4])
		print(COMMAND_NOT_FOUND, mini->args[4]);
	if (execve(mini->cmd1[4], args, mini->newenvp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void second_c(t_mini *mini, int i, int count)
{
	pid_t child2;
	child2 = fork();
	if (child2 == 0)
	{
		if (i != count)
			ft_child2(mini);
		else
			middle_pipe(mini);
	}
	else
		waitpid(-1, NULL, 0);
}
void ft_child1(t_mini *mini)
{
	char **args = ft_split(mini->args[0], ' ');
	close(mini->end[0]);
	dup2(mini->end[1], STDOUT_FILENO);
	close(mini->end[1]);
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
			pipe(mini->end);
			mini->child1 = fork();
			if (mini->child1 == 0)
				ft_child1(mini);
			else
				second_c(mini, i, count);
			close(mini->end[0]);
			close(mini->end[1]);
			waitpid(mini->child1, NULL, 0);
			waitpid(mini->child2, NULL, 0);
			i++;
		}
		return (1);
	}
}

void parsing(t_mini *mini)
{
	mini->args = ft_split(mini->str, ' ');
	put_cmd(mini);
	builtins(mini);
	if ((!ft_strcmp(mini->args[0], "cd")) || (!ft_strcmp(mini->args[0], "~")))
	{
		get_cd(mini->args[1], mini);
		return;
	}
	if (exec_pipes(mini) == 1)
		return;
	mini->newpro = fork();
	if (mini->newpro == 0)
	{
		if (!mini->cmd1[0])
			print(COMMAND_NOT_FOUND, mini->args[0]);
		else if (execve(mini->cmd1[0], mini->args, mini->newenvp) == -1)
			ft_exit(mini);
	}
	else
		waitpid(-1, NULL, 0);
}
