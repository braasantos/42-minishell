#include "../../inc/minishell.h"

void	handle_append2(t_mini *mini, int i)
{
	int	file;

	if (mini->args[i + 1])
	{
		file = open(mini->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (!file)
		{
			ft_fprintf(2, "Minishell: no file specified in redirect '>>'.\n");
			return ;
		}
		close(file);
	}
	else
		return ;
}

int	check_here(t_mini *mini)
{
	if (!ft_strcmp(mini->args[0], ">"))
	{
		check_parser2(mini, 1);
		return (1);
	}
	if (!ft_strcmp(mini->args[0], "<<"))
	{
		handle_heredoc(mini, mini->args[1]);
		return (1);
	}
	if (!ft_strcmp(mini->args[0], ">>"))
	{
		handle_append2(mini, 1);
		return (1);
	}
	return (0);
}

void	printf_errror()
{
	ft_fprintf(2, "Minishell: Permission denied\n");
}

int	do_redirects(t_mini *mini, int i)
{
	char	*s;
	int		file;

	if (!ft_strcmp(mini->args[i], ">>"))
	{
		if (mini->args[i + 1])
		{
			if (count_quotes(mini->args[i + 1]))
				s = ft_remove_quotes(mini->args[i + 1]);
			else
				s = ft_strdup(mini->args[i + 1]);
			file = open(s, O_WRONLY | O_CREAT | O_APPEND, 0664);
			if (access(s, W_OK) == -1)
				return (close(file), free(s), printf_errror(), 1);
			else
				return (close(file), free(s), 0);
		}
		g_signal = 1;
		ft_fprintf(2, "Minishell: syntax error ");
		ft_fprintf(2, "near unexpected token `newline'\n");
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
