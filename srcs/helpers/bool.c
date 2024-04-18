#include "../../inc/minishell.h"

bool	is_a_folder(char *s)
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

bool	check_options(char *s)
{
	if (is_a_pipe(s, 0) || is_a_red(s) || is_a_append_here(s))
		return (true);
	return (false);
}

bool	is_a_append_here(char *s)
{
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (true);
	return (false);
}

bool	is_a_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			return (true);
		i++;
	}
	return (false);
}
bool	is_a_option(char *s, t_mini *mini)
{
	char	*str;

	if (is_a_pipe(s, 0) || is_a_red(s) || is_a_file(s))
		return (false);
	if (!ft_strcmp(s, "-"))
		return (true);
	str = ft_add(mini, s);
	if (access(str, X_OK) == -1)
		return (free(str), true);
	else
		return (free(str), false);
}
