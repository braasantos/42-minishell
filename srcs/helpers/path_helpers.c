#include "../../inc/minishell.h"

void update_path(t_mini *mini, int i)
{
	mini->flag = 0;
	mini->path_to_cmd = ft_add(mini, mini->args[i]);
	if (count_pipes(mini) == 0 && count_red(mini) == 0 && str_len(mini->args) > 2)
	{
		mini->exec_args = add_option(mini);
		return;
	}
	if (str_len(mini->args) == 2)
	{
		if (mini->args[i + 1])
			if (is_a_option(mini->args[i + 1], mini) || is_a_file(mini->args[i + 1]) || is_a_cmd(mini->args[i + 1], mini))
				mini->exec_args = get_newenvp(mini->args);
	}
	else
		mini->exec_args = split_to_split(mini, i);
}

char **add_option(t_mini *mini)
{
	char *temp;
	char *result;
	char *new_result;
	char **ret;
	int i;

	result = NULL;
	i = 0;
	while (mini->args[i])
	{
		temp = ft_strjoin(mini->args[i], " ");
		if (result == NULL)
			result = ft_strdup(temp);
		else
		{
			new_result = ft_strjoin(result, temp);
			free(result);
			result = ft_strdup(new_result);
			free(new_result);
		}
		free(temp);
		i++;
	}
	ret = ft_split(result, ' ');
	free(result);
	return (ret);
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