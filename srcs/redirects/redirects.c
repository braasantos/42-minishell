#include "../../inc/minishell.h"

int change_ends_red(t_mini *mini, int flag)
{
	int fd;
	int file;

	file = check_position(mini, ">");
	fd = dup(STDOUT_FILENO);
	if (flag == 1)
	{
		if ((mini->fd1 = open(mini->args[file + 1], O_CREAT | O_RDWR | O_TRUNC, 0664)) < 0)
			return (0);
		dup2(mini->fd1, STDOUT_FILENO);
	}
	else
	{
		file = check_position(mini, "<");
		if ((mini->fd0 = open(mini->args[file - 1], O_RDONLY)) < 0)
			return (0);
		dup2(mini->fd0, STDIN_FILENO);
	}
	return (fd);
}

int check_position(t_mini *mini, char *to_find)
{
	int i;
	int j;

	i = 0;
	while (mini->args[i])
	{
		j = 0;
		while (to_find[j])
		{
			if (!ft_strcmp(mini->args[i], to_find))
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

void close_fd(t_mini *mini, int fd, int flag)
{
	if (flag == 1)
		dup2(fd, mini->fd1);
	else
		dup2(fd, mini->fd0);
	close(mini->fd1);
	close(mini->fd0);
}

void execute_first(t_mini *mini)
{
	int fd;

	if (have_redirect(mini) > 1)
	{
		if (have_redirect(mini) == 1) // >
		{
			fd = change_ends_red(mini, 1);
			// set_args(mini);
			// set_cmd(mini);
			// create_child(mini);
			close_fd(mini, fd, 1);
		}
		else // <
		{
			fd = change_ends_red(mini, 2);
			// set_args(mini);
			// set_cmd(mini);
			// create_child(mini);
			close_fd(mini, fd, 2);
		}
	}
}