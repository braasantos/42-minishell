#include "../../inc/minishell.h"

void ft_exit(t_mini *mini)
{
	ft_free_arr(mini->args);
	free(mini->new_str);
	ft_free_arr(mini->newenvp);
	exit(1);
}

void parsing(t_mini *mini, char *str)
{
	if (!ft_check_open_quotes(str))
		return;
	if (check_inutils(mini))
		return ;
	if (!redirect_basic_check(str))
		ft_printf("invalid redirect\n");
	if (!pipe_check(str))
		ft_printf("Minishell: syntax error near unexpected token ``|'\n");
	execute(mini);
}
void sigint_on_child(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void get_exit_status(t_mini *mini)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (i < count_pipes(mini) + 1)
	{
		signal(SIGINT, &sigint_on_child);
		waitpid(mini->newpro[i], &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_signal = 128 + WTERMSIG(status);
		i++;
	}
}
void through_pipes(t_mini *mini, int i)
{
	if (i == 0)
		dup2(mini->pipes_fd[1], STDOUT_FILENO);
	else if (i == count_pipes(mini))
		dup2(mini->pipes_fd[2 * i - 2], STDIN_FILENO);
	else
	{
		dup2(mini->pipes_fd[2 * i - 2], STDIN_FILENO);
		dup2(mini->pipes_fd[2 * i + 1], STDOUT_FILENO);
	}
	close_pipes(mini);
}

int count_red(t_mini *mini)
{
		int i;
	int count;

	i = 0;
	count = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "<") == 0 || ft_strcmp(mini->args[i], ">") == 0)
			count++;
		i++;
	}
	return (count);
}

int	redirect_output(int i, t_mini *mini)
{
	int		file_fd;

	if (!mini->args[i + 1])
		return (1);
	file_fd = open(mini->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (1);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (0);
}

int	redirect_input(int i, t_mini *mini)
{
	int		file_fd;

	file_fd = open(mini->args[i + 1], O_RDONLY);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '<'.\n", 2);
		return (1);
	}
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (0);
}
void	hanlde_redirects(t_mini *mini)
{
	int j;
	int count;

	j = 0;
	count = count_red(mini);
	if (count == 0)
		return ;
	else
	{
		while (mini->args[j])
		{
			if (!ft_strcmp(mini->args[j], ">"))
				redirect_output(j, mini);
			if (!ft_strcmp(mini->args[j], "<"))
				redirect_input(j, mini);
			if (!mini->args[j])
				return ;
			j++;
		}
	}
}

void	redirect(t_mini *mini)
{
	dup2(mini->stdin_fd, STDIN_FILENO);
	dup2(mini->stdout_fd, STDOUT_FILENO);
}

void create_child(t_mini *mini, int i, int flag, int j)
{
	update_path(mini, i);
	if (is_a_cmd(mini->args[i], mini) == false)
	{
		print(COMMAND_NOT_FOUND, mini->args[i]);
		return;
	}
	mini->newpro[j] = fork();
	if (!mini->newpro[j])
	{
		hanlde_redirects(mini);
		if (flag == 1)
			through_pipes(mini, j);
		redirect(mini);
		if (execve(mini->path_to_cmd, mini->exec_args, mini->newenvp) == -1)
			ft_exit(mini);
	}
	if (mini->exit_flag != 1 && flag == 0)
		get_exit_status(mini);
	delete_path(mini);
}
