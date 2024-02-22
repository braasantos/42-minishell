#include "../inc/minishell.h"

void ft_exit(t_mini *mini)
{
	free(mini->args);
	free(mini->new_str);
	free(mini->newenvp);
	exit(1);
}

void parsing(t_mini *mini, char *str)
{
	mini->new_str = pad_central(str);
	mini->args = ft_split(mini->new_str, ' ');
	put_cmd(mini, str);
	if (!ft_check_open_quotes(str))
		return;
	if (!redirect_basic_check(str))
		ft_printf("invalid redirect\n");
	if (!pipe_check(str))
		ft_printf("Unexpected near '|'\n");
	if (builtins(mini) == 1)
		return;
	execute(mini);
}

bool is_a_pipe(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

bool is_a_red(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			return (true);
		i++;
	}
	return (false);
}
bool is_a_cmd(char *s, t_mini *mini)
{
	char *str;

	str = ft_add(mini, s);
	if (access(str, X_OK) == 0)
		return (free(str), true);
	else
		return (free(str), false);
}
bool is_a_file(char *s)
{
	if (access(s, R_OK) == -1)
		return (false);
	return (true);
}

bool is_a_str(char *s, t_mini *mini)
{
	if (is_a_pipe(s) || is_a_red(s) || is_a_cmd(s, mini) || is_a_file(s))
		return (false);
	else
		return (true);
}

void execute(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (is_a_pipe(mini->args[i]))
			printf("%d pipe\n", i);
		if (is_a_red(mini->args[i]))
			printf("%d redirect\n", i);
		if (is_a_cmd(mini->args[i], mini))
			create_flow(mini);
		if (is_a_file(mini->args[i]))
			printf("%d file\n", i);
		if (is_a_str(mini->args[i], mini))
			printf("%d string\n", i);
		i++;
	}
	// execute_first(mini);
	// execute_second(mini);
}
void create_flow(t_mini *mini)
{
	if ((count_pipes(mini) == 0) && (have_redirect(mini) == 0))
		create_child(mini);
	else if ((count_pipes(mini) > 0) && (have_redirect(mini) == 0))
	{
		red_pipes(mini, 0);
		create_child(mini);
	}
}

void create_child(t_mini *mini)
{
	mini->newpro = fork();
	if (mini->newpro == 0)
	{
		if (!mini->path_to_cmd)
			print(COMMAND_NOT_FOUND, mini->exec_args[0]);
		else if (execve(mini->cmd1[0], mini->args, mini->newenvp) == -1)
			ft_exit(mini);
	}
	else
		waitpid(-1, NULL, 0);
}

// void set_args(t_mini *mini)
// {

// }
// void set_cmd(t_mini *mini)
// {
// 	if (!mini->cmd1)
// 		print(COMMAND_NOT_FOUND, mini->args[0]);
// }
