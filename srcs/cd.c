#include "../inc/minishell.h"

int find_env_var(char *var, t_mini *mini)
{
	int i;
	char *tmp;

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
char **realloc_envv(int new_size, t_mini *mini)
{
	char **new;
	int i;

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

void set_env_var(char *key, char *value, t_mini *mini)
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

int ft_strendswith(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s1[++i])
		if (s1[i] == s2[0])
			if (ft_strcmp(s1 + i, s2) == 0)
				return (1);
	return (0);
}

char *ft_pathjoin(char *p1, char *p2)
{
	char *tmp2;

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

char *get_env(char *var, t_mini *mini)
{
	int i;
	char *tmp;

	i = -1;
	while (mini->newenvp[++i])
	{
		tmp = ft_strjoin(var, "=");
		if (ft_strstartswith(mini->newenvp[i], tmp))
		{
			free(tmp);
			return (ft_strchr(mini->newenvp[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

void change_dir(char *path, t_mini *mini)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	if (!chdir(path))
		set_env_var("OLDPWD", cwd, mini);
	else
	{
		ft_printf("cd: ");
		if (access(path, F_OK) == -1)
			ft_printf("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_printf("permission denied: ");
		else
			ft_printf("not a directory: ");
		ft_putendl_fd(path, 1);
	}
}

static int has_two_args(char **args, t_mini *mini)
{
	if (args[1])
	{
		if (args[2])
		{
			ft_putendl_fd("cd: too many arguments", 1);
			return (1);
		}
		change_dir(args[1], mini);
		return (1);
	}
	return (0);
}

int get_cd(t_mini *mini)
{
	char *home_dir;

	home_dir = get_env("HOME", mini);
	if ((!mini->args[1]) || (!ft_strcmp(mini->args[0], "~")))
	{
		change_dir(home_dir, mini);
		return (1);
	}
	if (has_two_args(mini->args, mini))
		return (1);
	else if (mini->args[0][0] == '-')
	{
		change_dir(get_env("OLDPWD", mini), mini);
		return (1);
	}
	return (0);
}

int ft_strstartswith(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}
