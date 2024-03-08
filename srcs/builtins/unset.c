#include "../../inc/minishell.h"

char **remove_var(char **newenvp, char *var_name)
{
    int num_vars;
    int i;
	int j;
    char **newenvp_new;

	num_vars = 0;
	i = 0;
    while (newenvp[num_vars])
	{
        num_vars++;
	}
    newenvp_new = (char **)malloc((num_vars + 1) * sizeof(char *));
    j = 0;
    while (newenvp[i])
	{
        if (ft_strncmp(newenvp[i], var_name, ft_strlen(var_name)) != 0)
		{
            newenvp_new[j] = (char *)malloc((ft_strlen(newenvp[i]) + 1) * sizeof(char));
            ft_strcpy(newenvp_new[j], newenvp[i]);
            j++;
        }
        i++;
    }
    newenvp_new[j] = NULL;
    return (newenvp_new);
}

int get_unset(t_mini *mini)
{
	char *var_name;
	char **newvar;

	if (mini->args[1])
	{
		var_name = ft_strdup(mini->args[1]);
		newvar = remove_var(mini->newenvp, var_name);
		ft_free_arr(mini->newenvp);
		mini->newenvp = get_newenvp(newvar);
		ft_free_arr(newvar);
		free(var_name);
	}
	return (1);
}