#include "../../inc/minishell.h"

int str_len(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int have_redirect(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], ">") == 0)
			return (1);
		if (ft_strcmp(mini->args[i], "<") == 0)
			return (2);
		i++;
	}
	return (0);
}

int builtins(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "exit"))
	{
		mini->exit_flag = 1;
		unlink(".heredoc");
		free_struct_2(mini);
	}
	if (!ft_strcmp(mini->args[0], "pwd"))
		return (print_pwd());
	if (!ft_strcmp(mini->args[0], "echo"))
<<<<<<< HEAD
		return (echo_cmd(mini));
	if ((!ft_strcmp(mini->args[0], "cd")))
=======
		return (echo_cmd(mini->args, mini));
	if ((!ft_strcmp(mini->args[0], "cd")) || (!ft_strcmp(mini->args[0], "~")))
>>>>>>> refs/remotes/origin/master
		return (get_cd(mini));
	if ((!ft_strcmp(mini->args[0], "env")))
		return (get_envp(mini));
	if ((!ft_strcmp(mini->args[0], "export")))
		return (get_export(mini));
	if ((!ft_strcmp(mini->args[0], "unset")))
		return (get_unset(mini));
	return (0);
}

int check_parser2(t_mini *mini, int i)
{
	int file_fd;

	file_fd = 0;
	file_fd = open(mini->args[i], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!file_fd)
	{
		ft_putstr_fd("Minishell: no file specified in redirect '>'.\n", 2);
		return (1);
	}
	return (0);
}
