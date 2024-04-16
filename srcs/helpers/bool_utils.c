#include "../../inc/minishell.h"

bool	is_a_pipe(char *s, int flag)
{
	int	i;

	i = 0;
	if (flag)
	{
		if (!ft_strcmp(s, "|"))
			return (true);
		else
			return (false);
	}
	else
	{
		while (s[i])
		{
			if (s[i] == '|')
				return (true);
			i++;
		}
	}
	return (false);
}

bool	is_a_red(char *s)
{
	int	i;

	i = 0;
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (true);
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			return (true);
		i++;
	}
	return (false);
}

bool	is_a_quote(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			count++;
		i++;
	}
	if (count == i)
		return (true);
	return (false);
}

bool	is_a_cmd(char *s, t_mini *mini)
{
	char	*str;
	char	*temp;
	bool	result;

	result = false;
	if (is_a_quote(s))
		return (result);
	if (count_quotes(mini->new_str) > 0)
		temp = ft_remove_quotes(s);
	else
		temp = ft_strdup(s);
	str = ft_add(mini, temp);
	if (!str)
	{
		free(temp);
		return (false);
	}
	if (str)
	{
		if (access(str, X_OK) == 0)
			result = true;
		free(str);
	}
	free(temp);
	return (result);
}

bool	is_a_file(char *s)
{
	char	*str;

	if (count_quotes(s))
		str = ft_remove_quotes(s);
	else
		str = ft_strdup(s);
	if (access(str, F_OK) == -1)
		return (free(str), false);
	return (free(str), true);
}