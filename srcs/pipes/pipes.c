#include "../../inc/minishell.h"

int isPipeOpen(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1)
	{
		perror("fcntl");
		return -1; // Error occurred
	}

	// Check if the file descriptor is open
	if ((flags & O_ACCMODE) == O_RDONLY || (flags & O_ACCMODE) == O_RDWR)
	{
		// The file descriptor is open for reading
		return 1;
	}
	else
	{
		// The file descriptor is not open for reading
		return 0;
	}
}

int isPipeOpenForWriting(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1)
	{
		perror("fcntl");
		return -1; // Error occurred
	}

	// Check if the file descriptor is open for writing
	if ((flags & O_ACCMODE) == O_WRONLY || (flags & O_ACCMODE) == O_RDWR)
	{
		// The file descriptor is open for writing
		return 1;
	}
	else
	{
		// The file descriptor is not open for writing
		return 0;
	}
}

void middle_pipe(t_mini *mini)
{
	close(mini->end[1]);
	dup2(mini->end[0], STDIN_FILENO);
	close(mini->end[0]);
	dup2(mini->end[1], STDOUT_FILENO);
	close(mini->end[1]);
}
void close_final(t_mini *mini)
{
	close(mini->end[1]);
	dup2(mini->end[0], STDIN_FILENO);
	close(mini->end[0]);
}

void firs_pipe(t_mini *mini, char *s)
{
	close(mini->end[0]);
	dup2(mini->end[1], STDOUT_FILENO);
	close(mini->end[1]);
	ft_child1(mini, s);
}
void ft_child1(t_mini *mini, char *s)
{
	update_path(mini, s);
	if (is_a_cmd(s, mini) == false)
	{
		print(COMMAND_NOT_FOUND, s);
		return;
	}
	if (execve(mini->path_to_cmd, mini->exec_args, mini->newenvp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void ft_child2(t_mini *mini)
{
	int pos;
	pos = check_position(mini, "|");
	update_path(mini, mini->args[pos + 1]);
	if (is_a_cmd(mini->args[pos + 1], mini) == false)
	{
		print(COMMAND_NOT_FOUND, mini->args[pos + 1]);
		return;
	}
	if (execve(mini->path_to_cmd, mini->exec_args, mini->newenvp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}