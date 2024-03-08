#include "../../inc/minishell.h"

char **add_var(char **newenvp, char *new_var)
{
	int num_vars;
	int i;
	char **newenvp_new;

	num_vars = str_len(newenvp);
	i = 0;
	newenvp_new = malloc((num_vars + 2) * sizeof(char *));
	if (newenvp_new == NULL)
		return NULL;
	while (i < num_vars)
	{
		newenvp_new[i] = malloc((ft_strlen(newenvp[i]) + 1) * sizeof(char));
		ft_strcpy(newenvp_new[i], newenvp[i]);
		i++;
	}
	newenvp_new[num_vars] = malloc((ft_strlen(new_var) + 1) * sizeof(char));
	ft_strcpy(newenvp_new[num_vars], new_var);
	newenvp_new[num_vars + 1] = NULL;
	return (newenvp_new);
}


int get_export(t_mini *mini)
{
	char **newvar;

	newvar = NULL;
	if (mini->args[1])
	{
		if (count_quotes(mini->new_str) == 0)
			export_quotes(newvar, mini);
		else if (count_quotes(mini->new_str) > 0)
			export_woquotes(newvar, mini);
	}
	return (1);
}

void	export_quotes(char **newvar, t_mini *mini)
{
	char *var;

	var = ft_strdup(mini->args[1]);
	newvar = add_var(mini->newenvp, var);
	ft_free_arr(mini->newenvp);
	mini->newenvp = get_newenvp(newvar);
	ft_free_arr(newvar);
	free(var);
}

void	export_woquotes(char **newvar, t_mini *mini)
{
	char **splitted;
	char *str;
	char *tmp;

	splitted = ft_split(mini->new_str, '\"');
	str = help(splitted[0]);
	tmp = ft_strjoin(str, splitted[1]);
	free(str);
	newvar = add_var(mini->newenvp, tmp);
	free(tmp);
	ft_free_arr(mini->newenvp);
	mini->newenvp = get_newenvp(newvar);
	ft_free_arr(newvar);
	ft_free_arr(splitted);
}
