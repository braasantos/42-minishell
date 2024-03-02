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

char *do_sum(t_mini *mini, int i)
{
	char *s;

	if (count_quotes(mini->args[i + 1]) > 1)
		s = ft_remove_quotes(mini->args[i + 1]);
	else
		s = ft_strdup(mini->args[i + 1]);
	return (s);
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

char	*ft_remove_quotes(char *str)
{
	char	*new;
	int	count;
	int	i;
	int	j;

	count = count_quotes(str);
	i = ft_strlen(str) - count;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

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