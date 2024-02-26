#include "../../inc/minishell.h"

int str_len(char **str)
{
	int i = 0;

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
		ft_exit(mini);
	}
	if (!ft_strcmp(mini->args[0], "echo"))
		return (echo_cmd(mini->args));
	if ((!ft_strcmp(mini->args[0], "cd")) || (!ft_strcmp(mini->args[0], "~")))
		return (get_cd(mini));
	return (0);
}
