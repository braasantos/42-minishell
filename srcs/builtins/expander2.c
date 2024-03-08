#include "../../inc/minishell.h"

void do_strjoin(int i, char *env, t_mini *mini)
{
	free(mini->args[i]);
	mini->args[i] = ft_strjoin(mini->before, env);
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
		space = malloc(2 * sizeof(char));
    	space[0] = ' ';
    	space[1] = '\0';
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

	j = 0;
	i = ft_strlen(s) - 1;
	while (i >= 0 && !isalnum(s[i]))
	{
		i--;
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