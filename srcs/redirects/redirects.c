#include "../../inc/minishell.h"

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