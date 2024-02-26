#include "../../inc/minishell.h"

int check_position_bool(t_mini *mini, char *to_find)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], to_find))
			return i;
		i++;
	}
	return 0;
}

int check_position(t_mini *mini, int j)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], mini->args[j]))
			return i;
		i++;
	}
	return 0;
}