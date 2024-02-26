#include "../../inc/minishell.h"
bool is_a_file_to_create(char *s, t_mini *mini)
{
	int pos;

	pos = check_position_bool(mini, ">");
	if ((is_a_red(mini->args[pos])))
	{
		if (is_a_option(s, mini))
			return (true);
	}
	return (false);
}

void create_file(t_mini *mini)
{
	int file;

	file = check_position_bool(mini, "<");
	printf("%d\n", file);
	mini->STDOUT = dup(STDOUT_FILENO);
	if ((mini->fd0 = open(mini->args[file + 1], O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
		return;
	}
	dup2(mini->fd0, STDIN_FILENO);
}

char **split_to_split(t_mini *mini, char *s)
{
	int pos;
	char *temp = NULL;
	char *str = NULL;
	char **new_str = NULL;

	pos = check_position_bool(mini, s);
	if (mini->args[pos + 1])
	{
		if (is_a_option(mini->args[pos + 1], mini))
		{
			str = ft_strdup(mini->args[pos]);
			temp = ft_strjoin(str, " ");
			free(str);
			str = ft_strjoin(temp, mini->args[pos + 1]);
			free(temp);
			new_str = ft_split(str, ' ');
			free(str);
			if (!new_str)
				return (ft_free_arr(new_str), NULL);
			else
				return (new_str);
		}
	}
	return (ft_split(s, ' '));
}

void update_path(t_mini *mini, int i)
{
	mini->path_to_cmd = ft_add(mini, mini->args[i]);
	if (str_len(mini->args) == 2)
	{
		if (mini->args[i + 1])
			if (is_a_option(mini->args[i + 1], mini))
				mini->exec_args = get_newenvp(mini->args);
	}
	else
		mini->exec_args = split_to_split(mini, mini->args[i]);
}

void delete_path(t_mini *mini)
{
	free(mini->path_to_cmd);
	ft_free_arr(mini->exec_args);
}