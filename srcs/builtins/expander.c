#include "../../inc/minishell.h"

int bingo(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

char *get_expand(char *s)
{
	int i;
	char *str;
	int len;
	int j;

	i = 0;
	j = 0;
	len = ft_strlen(s) - 1;
	str = malloc(sizeof(char) * (len + 2));
	while (s[i] != '$')
		i++;
	while (s[i])
	{
		if (s[i] == '$')
			i++;
		else
			str[j++] = s[i++];
		if (s[i] == '\'' || s[i] == ' ')
			break ;
	}
	str[j] = '\0';
	return (str);
}
int expander_squotes(t_mini *mini, int i)
{
	char **split;

	split = ft_split(mini->new_str, '\"');
	if (count_dquotes(mini->new_str) > 0)
	{
		if (ft_strstartswith(split[1], "\'"))
		{
			ft_free_arr(split);
			return (0);
		}
	}
	else
	{
		if (ft_strstartswith(mini->args[i], "\'"))
		{
			ft_free_arr(split);
			return (1);
		}
	}
	ft_free_arr(split);
	return (0);
}

int check_expand(t_mini *mini)
{
	int i;
	char *str;
	char *env;

	i = 0;
	while (mini->args[i])
	{
		if (bingo(mini->args[i], '$'))
		{
			if (expander_squotes(mini, i))
				return (0);
			str = get_expand(mini->args[i]);
			env = get_env(str, mini);
			free(str);
			if (env == NULL)
				return (free(env), do_strdup(i, env, mini, 0), 0);
			mini->before = ft_before(mini->args[i]);
			if (count_dquotes(mini->new_str) > 0)
				do_strjoin(i, env, mini);
			else
				do_strdup(i, env, mini, 1);
		}
		i++;
	}
	return (0);
}

void do_strdup(int i, char *env, t_mini *mini, int flag)
{
	free(mini->args[i]);
	if (flag == 1)
	{
		mini->args[i] = ft_strjoin(mini->before, env);
		free(mini->before);
	}
	else
		mini->args[i] = ft_strdup("\0");
}
