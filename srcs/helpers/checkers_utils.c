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
