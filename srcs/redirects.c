#include "../inc/minishell.h"

int redirect_cmd(t_mini *mini)
{
	if (check_red(mini) == 1)
		if (execute_rd_one(mini) == 1)
			return (0);
	// else
	// 	if (execute_rd_two(mini) == 1)
	// 		return (0);
	return (0);
}

int execute_rd_one(t_mini *mini)
{
	int len;
	int	fd;
	char **args;

	len = str_len(mini->args);
	if ((mini->fd1 = open(mini->args[len - 1], O_CREAT | O_RDWR | O_TRUNC, 0664)) < 0)
		return (1);
	args = ft_split(mini->args[0], ' ');
	fd = dup(STDOUT_FILENO);
	dup2(mini->fd1, STDOUT_FILENO);
	pid_t pid = fork();
	if (!pid)
	{
		if (!mini->cmd1[0])
			print(COMMAND_NOT_FOUND, mini->args[0]);
		else if (execve(mini->cmd1[0], args, mini->newenvp) == -1)
			ft_exit(mini);
	}
	else
		waitpid(-1, NULL, 0);
	close(mini->fd1);
	dup2(fd, mini->fd1);
	return (1);
}


// int redirect_cmd1(t_mini *mini) {
//     int len;

//     if (check_red(mini) == 2)
//         return (0);
//     else {
//         len = str_len(mini->args);
//         char **args = ft_split(mini->args[0], ' ');
//         if ((mini->fd0 = open(mini->args[len - 1], O_RDONLY)) < 0)
//             return (1);
//         if (isatty(STDIN_FILENO)) { // Check if stdin is connected to a terminal
//             dup2(mini->fd0, STDIN_FILENO);
//             mini->newpro = fork();
//             if (mini->newpro == 0) {
//                 if (!mini->cmd1[0])
//                     print(COMMAND_NOT_FOUND, mini->args[0]);
//                 else if (execve(mini->cmd1[0], args, mini->newenvp) == -1)
//                     ft_exit(mini);
//             } else {
//                 close(mini->fd0);
//                 waitpid(mini->newpro, NULL, 0);
//             }
//         }
//         return (1);
//     }
// }
