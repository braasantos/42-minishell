#include "../../inc/minishell.h"

bool is_a_pipe(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

bool is_a_red(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			return (true);
		i++;
	}
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (true);
	return (false);
}
bool is_a_cmd(char *s, t_mini *mini)
{
	char *str;
	char *temp;

	if (count_quotes(s) > 0)
		temp = ft_remove_quotes(s);
	else
		temp = ft_strdup(s);
	str = ft_add(mini, temp);
	if (access(str, X_OK) == 0)
		return (free(temp), free(str), true);
	else
		return (free(temp), free(str), false);
}
bool is_a_file(char *s)
{
	if (access(s, R_OK) == -1)
		return (false);
	return (true);
}

bool is_a_option(char *s, t_mini *mini)
{
	char *str;

	if (is_a_pipe(s) || is_a_red(s) || is_a_file(s))
		return (false);
	if (!ft_strcmp(s, "-"))
		return (true);
	str = ft_add(mini, s);
	if (access(str, X_OK) == -1)
		return (free(str), true);
	else
		return (free(str), false);
}

