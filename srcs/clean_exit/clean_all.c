#include "../../inc/minishell.h"

void ft_free_arr(char **str)
{
	int i;

	if (!str)
		return;
	
	i = -1;
	while (str[++i])
	{
		if (str[i])
			free(str[i]);
	}
	free(str);
	str = NULL;
}

void free_struct(t_mini *mini)
{
	if (mini->args)
		ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
}

void free_struct_2(t_mini *mini)
{
	if (mini->args)
		ft_free_arr(mini->args);
	if (mini->new_str)
		free(mini->new_str);
	if (mini->str)
		free(mini->str);
	if (mini->newenvp)
		ft_free_arr(mini->newenvp);
	exit(1);
}