#include "../../inc/minishell.h"

int	print_pwd(t_mini *mini, int i)
{
	char	*env;

	if (!mini->args[i + 1])
	{
		env = getcwd(0, 0);
		ft_printf("%s\n", env);
		free(env);
		return (1);
	}
	else
		printf("Minishell: pwd with options\n");
	return (1);
}