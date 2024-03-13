#include "../../inc/minishell.h"

void execute(t_mini *mini)
{
	int n_pipes;

	n_pipes = count_pipes(mini);
	if (!ft_strcmp(mini->args[0], "echo"))
	{
		echo_cmd(mini->args, mini);
		return;
	}
	if (check_parser(mini) == 1)
		return;
	if ((n_pipes == 0))
	{
		if (is_a_builtin(mini, 0))
			if (builtins(mini, 0))
				return;
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

bool is_not_a_cmd(char *s)
{
	if (is_a_pipe(s) || is_a_red(s) || ft_strstartswith(s, "-") ||
		count_quotes(s) > 0 || is_a_append_here(s) || is_a_file(s) || is_a_number(s))
		return (false);
	return (true);
}

void create_flow(t_mini *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	pipe_creation(mini);
	while (mini->args[i])
	{
		if (check_next(mini, i))
			break;
		if (is_not_a_cmd(mini->args[i]))
		{
			if (create_child(mini, i, 1, j) == 1)
				break;
			j++;
		}
		i++;
	}
	close_pipes(mini);
	get_exit_status(mini);
}

void ft_exit_builtin(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "exit"))
	{
		mini->exit_flag = 1;
		unlink(".heredoc");
		free_struct_2(mini);
	}
}
int create_child(t_mini *mini, int i, int flag, int j)
{
	ft_exit_builtin(mini, i);
	if (is_a_cmd(mini->args[i], mini) == false && is_a_builtin(mini, i) == false)
		return (print(COMMAND_NOT_FOUND, mini->args[i]));
	if (is_a_builtin(mini, i) == false)
		update_path(mini, i);
	mini->newpro[j] = fork();
	if (!mini->newpro[j])
	{
		hanlde_redirects(mini);
		if (flag == 1)
			through_pipes(mini, j);
		redirect(mini);
		if (builtins(mini, i))
			exit(0);
		if (is_a_builtin(mini, i) == false)
			if (execve(mini->path_to_cmd, mini->exec_args, mini->newenvp) == -1)
				ft_exit(mini);
	}
	if (mini->exit_flag != 1 && flag == 0)
		get_exit_status(mini);
	if (is_a_builtin(mini, i) == false)
		delete_path(mini);
	return (0);
}
