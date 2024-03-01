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
int count_quotes(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
            count++;
        i++;
    }
    return count;
}


char *no_quote(char *str)
{
	int i;
	int j;
	char *s;

	i = ft_strlen(str);
	i--;
	j = count_quotes(str);
	s = malloc(sizeof(char) * (i + 1 - j));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
            i++;
		s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\0';
	printf("%s\n", str);
	printf("%s\n", s);
	return (s);
}

void update_path(t_mini *mini, int i)
{
	int j = 0;
	mini->flag = 0;
	mini->path_to_cmd = ft_add(mini, mini->args[i]);
	if (str_len(mini->args) == 2)
	{
		if (mini->args[i + 1])
			if (is_a_option(mini->args[i + 1], mini) || is_a_file(mini->args[i + 1]))
				mini->exec_args = get_newenvp(mini->args);
	}
	else
		mini->exec_args = split_to_split(mini, mini->args[i]);
	while (mini->exec_args[j])
	{
		if (!ft_strcmp(mini->exec_args[j], "\'") || !ft_strcmp(mini->exec_args[j], "\""))
		{
			free(mini->exec_args[j]);
			mini->exec_args[j] = ft_strdup(no_quote(mini->exec_args[j]));
		}
		j++;
	}
}

void delete_path(t_mini *mini)
{
	free(mini->path_to_cmd);
	ft_free_arr(mini->exec_args);
}