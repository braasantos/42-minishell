#include "../../inc/minishell.h"

void update_path(t_mini *mini, int i)
{
	mini->flag = 0;
	mini->path_to_cmd = ft_add(mini, mini->args[i]);
	if (str_len(mini->args) == 2)
	{
		if (mini->args[i + 1])
			if (is_a_option(mini->args[i + 1], mini) || is_a_file(mini->args[i + 1]))
				mini->exec_args = get_newenvp(mini->args);
	}
	else
		mini->exec_args = split_to_split(mini, i);
}

void delete_path(t_mini *mini)
{
	free(mini->path_to_cmd);
	ft_free_arr(mini->exec_args);
}

char **split_to_split(t_mini *mini, int i)
{
	char *temp;
	char *str;
	char **new_str;
	char *no_quotes;

	if (mini->args[i + 1])
	{
		if (is_a_option(mini->args[i + 1], mini))
		{
			no_quotes = do_sum(mini, i);
			str = ft_strdup(mini->args[i]);
			temp = ft_strjoin(str, " ");
			free(str);
			str = ft_strjoin(temp, no_quotes);
			free(temp);
			free(no_quotes);
			new_str = ft_split(str, ' ');
			free(str);
			if (!new_str)
				return (ft_free_arr(new_str), NULL);
			else
				return (new_str);
		}
	}
	return (ft_split(mini->args[i], ' '));
}