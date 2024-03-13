#include "../../inc/minishell.h"

int count_squotes(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            count++;
        i++;
    }
    return count;
}

void while_loop(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		ft_printf("%s\n", s[i]);
		i++;
	}
}