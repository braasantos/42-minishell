#include "../../inc/minishell.h"

int print_pwd(void)
{
	char *env;

	env = getcwd(0, 0);
	ft_printf("%s\n", env);
	free(env);
	return (1);
}