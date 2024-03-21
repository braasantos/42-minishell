#include "../../inc/minishell.h"

int	find_env_var(char *var, t_mini *mini)
{
	int		i;
	char	*tmp;

	i = -1;
	while (mini->newenvp[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_strstartswith(mini->newenvp[i], tmp))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
	}
	return (i);
}
char	**realloc_envv(int new_size, t_mini *mini)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (mini->newenvp[++i] && i < new_size)
	{
		new[i] = ft_strdup(mini->newenvp[i]);
		free(mini->newenvp[i]);
	}
	free(mini->newenvp);
	return (new);
}

void	set_env_var(char *key, char *value, t_mini *mini)
{
	int pos;
	char *tmp;

	pos = find_env_var(key, mini);
	tmp = ft_strjoin("=", value);
	if (mini->newenvp[pos])
	{
		free(mini->newenvp[pos]);
		if (value)
			mini->newenvp[pos] = ft_strjoin(key, tmp);
		else
			mini->newenvp[pos] = ft_strjoin(key, "=");
	}
	else
	{
		mini->newenvp = realloc_envv(pos + 1, mini);
		if (value)
			mini->newenvp[pos] = ft_strjoin(key, tmp);
		else
			mini->newenvp[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
}

int	ft_strendswith(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s1[++i])
		if (s1[i] == s2[0])
			if (ft_strcmp(s1 + i, s2) == 0)
				return (1);
	return (0);
}

char	*ft_pathjoin(char *p1, char *p2)
{
	char	*tmp2;

	if (!p2 || !p1)
		return (NULL);
	if (!ft_strendswith(p1, "/"))
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2));
		else
		{
			tmp2 = ft_strjoin(ft_strjoin(p1, "/"), p2);
			return (tmp2);
		}
	}
	else
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2 + 1));
		else
			return (ft_strjoin(p1, p2));
	}
}
