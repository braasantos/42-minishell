#include "../../inc/minishell.h"

void do_strjoin(int i, char *env, t_mini *mini)
{
	char *temp;

	mini->after = ft_after(mini->new_str);
	temp = ft_strjoin(mini->before, env);
	free(mini->args[i]);
	mini->args[i] = ft_strjoin(temp, mini->after);
	free(temp);
	free(mini->after);
	free(mini->before);
}
void free_expand(char *s1, char *s2, char *s3, int flag)
{
	free(s3);
	free(s1);
	free(s2);
	if (flag == 1)
		s3 = ft_strdup(" ");
}
int ft_var(char *str)
{
	int i;

	i = ft_before_exp(str);
	if (str[i] && str[i] == '$')
		i++;
	if (count_squotes(str) > 0)
	{
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			i--;
	}
	else
	{
		while (str[i] && str[i] != ' ')
			i++;
		if (str[i] == ' ')
			i--;
	}
	return (i);
}

int ft_before_exp(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}


char *ft_before(char *s)
{
	int i;
	char *before_quo;
	char *space;
	int j;

	i = ft_before_exp(s);
	if (i == 0)
	{
		space = malloc(1 * sizeof(char));
		space[0] = '\0';
		return (space);
	}
	before_quo = malloc(sizeof(char) * (i + 1));
	if (before_quo == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		before_quo[j] = s[j];
		j++;
	}
	before_quo[j] = '\0';
	return (before_quo);
}

char *ft_after(char *s)
{
	int i;
	int j;
	char *after_quo;
	int k;
	int len;

	j = 0;
	i = ft_var(s);
	len = ft_strlen(s) - 1 - i;
	while (len >= 0)
	{
		len--;
		j++;
	}
	after_quo = malloc(sizeof(char) * (j + 1));
	k = 0;
	while (k < j)
	{
		after_quo[k] = s[i + k + 1];
		k++;
	}
	after_quo[k] = '\0';
	return (after_quo);
}
