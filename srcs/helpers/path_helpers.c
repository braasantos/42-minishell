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
	else if (!ft_strcmp(mini->args[i], "head"))
		mini->exec_args = another_split(mini, i);
	else
		mini->exec_args = split_to_split(mini, i);
}
char **another_split(t_mini *mini, int i)
{
	char **new_str;
	char *temp;
	char *str;
	char *no_quotes;

	if (mini->args[i + 1])
	{
		if (is_a_option(mini->args[i + 1], mini) || is_a_folder(mini->args[i + 1]))
		{
			no_quotes = do_sum(mini, i);
			temp = give_first(no_quotes, mini, i);
			if (mini->args[i + 2])
			{
				if (is_a_number(mini->args[i + 2]) || is_a_file(mini->args[i + 2]))
					str = ft_strjoin(temp, mini->args[i + 2]);
				new_str = ft_split(str, ' ');
			}
			else
				new_str = ft_split(temp, ' ');
			free(str);
			if (!new_str)
				return (free(temp), ft_free_arr(new_str), NULL);
			else
				return (free(temp), new_str);
		}
	}
	return (ft_split(mini->args[i], ' '));
}

char *give_first(char *no_quotes, t_mini *mini, int i)
{
	char *str;
	char *temp;

	str = ft_strdup(mini->args[i]);
	temp = ft_strjoin(str, " ");
	free(str);
	str = ft_strjoin(temp, no_quotes);
	free(temp);
	free(no_quotes);
	return (str);
}

static	char *hndl_quotes(t_mini *mini, int i)
{
	char *s;
	char *temp;

	if (count_dquotes(mini->args[i]) > 0)
		s = ft_remove_quotes(mini->args[i]);
	else
		s = ft_strdup(mini->args[i]);
	temp = ft_strjoin(s, " ");
	free(s);
	return (temp);
}


char **add_option(t_mini *mini)
{
	char *temp;
	char *result;
	char *new_result;
	char **ret;
	int i;

	result = NULL;
	i = -1;
	while (mini->args[++i])
	{
		temp = hndl_quotes(mini, i);
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
		if (is_a_option(mini->args[i + 1], mini) || is_a_folder(mini->args[i + 1]))
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
char *ft_touppercase(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - ('a' - 'A');
		i++;
	}
	return (s);
}