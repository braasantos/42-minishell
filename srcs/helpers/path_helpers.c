#include "../../inc/minishell.h"

void	update_path(t_mini *mini, int i)
{
	char	*temp;

	temp = NULL;
	mini->flag = 0;
	mini->path_to_cmd = ft_add(mini, mini->args[i]);
	mini->exec_args = add_option(mini, i, temp);
}

char	*hndl_quotes(t_mini *mini, int i)
{
	char	*s;
	char	*temp;

	s = NULL;
	temp = NULL;
	if (count_dquotes(mini->args[i]) > 0)
		s = ft_remove_quotes(mini->args[i]);
	else
		s = ft_strdup(mini->args[i]);
	temp = ft_strjoin(s, " ");
	free(s);
	return (temp);
}


int save_lines2(t_mini *mini, char *temp, int i)
{
	if (check_options(mini->args[i]))
	{
		mini->pipe_or_redirect_found = true;
		free(temp);
		return (1);
	}
	return (0);
}

char	**add_option(t_mini *mini, int i, char *temp)
{
	char	*result;
	char	*new_result;
	char	**ret;

	result = NULL;
	mini->pipe_or_redirect_found = false;
	while (mini->args[i] && !mini->pipe_or_redirect_found)
	{
		temp = hndl_quotes(mini, i);
		if (result == NULL)
			result = ft_strdup(temp);
		else
		{
			if (save_lines2(mini, temp, i))
				break;
			new_result = ft_strjoin(result, temp);
			free(result);
			result = ft_strdup(new_result);
			free(new_result);
		}
		free(temp);
		i++;
	}
	ret = ft_split(result, ' ');
	return (free(result), ret);
}

void	delete_path(t_mini *mini)
{
	free(mini->path_to_cmd);
	ft_free_arr(mini->exec_args);
}
