#include "../../inc/minishell.h"

void	handle_append2(t_mini *mini, int i)
{
	int	file;

	if (mini->args[i + 1])
	{
		file = open(mini->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (!file)
		{
			ft_putstr_fd("Minishell: no file specified in redirect '>>'.\n", 2);
			return ;
		}
		close(file);
	}
	else
		return ;
}

int	check_here(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], "<<"))
	{
		handle_heredoc(mini, 0);
		return (1);
	}
	if (!ft_strcmp(mini->args[0], ">>"))
	{
		handle_append2(mini, 0);
		return (1);
	}
	return (0);
}

int	do_redirects(t_mini *mini, int i)
{
	if (!ft_strcmp(mini->args[i], "<<"))
	{
		if (mini->args[i + 1])
			return (0);
		else
		{
			g_signal = 2;
			ft_putstr_fd("Minishell: syntax error ", 2);
			ft_putendl_fd("near unexpected token `newline'", 2);
			return (1);
		}
	}
	if (!ft_strcmp(mini->args[i], ">>"))
	{
		if (mini->args[i + 1])
			return (0);
		else
		g_signal = 1;
		ft_putstr_fd("Minishell: syntax error ", 2);
		ft_putendl_fd("near unexpected token `newline'", 2);
		return (1);
	}
	return (0);
}

int	have_here_doc(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}