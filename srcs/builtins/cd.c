#include "../../inc/minishell.h"

char *get_env(char *var, t_mini *mini)
{
	int i;
	char *tmp;
	char *str;

	i = -1;
	str = ft_remove_quotes(var);
	while (mini->newenvp[++i])
	{
		tmp = ft_strjoin(str, "=");
		if (ft_strstartswith(mini->newenvp[i], tmp))
		{
			free(tmp);
			free(str);
			return (ft_strchr(mini->newenvp[i], '=') + 1);
		}
		free(tmp);
	}
	free(str);
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

int get_cd(t_mini *mini, int i)
{
	char *home_dir;

	home_dir = get_env("HOME", mini);
	if ((!mini->args[i + 1]))
	{
		change_dir(home_dir, mini);
		return (1);
	}
	else
	{
		if (is_a_pipe(mini->args[i + 1]) || is_a_red(mini->args[i + 1]) || is_a_append_here(mini->args[i + 1]))
			return (1);
		if (has_two_args(mini->args, mini))
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
