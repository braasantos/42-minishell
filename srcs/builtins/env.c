#include "../../inc/minishell.h"

int	get_envp(t_mini *mini)
{
	int	i;

	i = -1;
	while(mini->newenvp[++i])
		printf("%s\n", mini->newenvp[i]);
	return (1);
}