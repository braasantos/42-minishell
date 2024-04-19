#include "../../inc/minishell.h"

char	*ft_after_expander(char *s)
{
	int		j;
	int		len;
	char	*after_quo;
	int		k;

	j = 0;
	len = ft_strlen(s);
	len --;
	while (s[len] && !ft_isalpha(s[len]))
	{
		len--;
		j++;
	}
	after_quo = malloc(sizeof(char) * (j + 1));
	k = 0;
	len = ft_strlen(s);
	len --;
	while (s[len] && !ft_isalpha(s[len]))
	{
		after_quo[k++] = s[len];
		len--;
	}
	after_quo[k] = '\0';
	return (after_quo);
}

void	free_expand2(t_mini *mini, int flag, int i)
{
	if (flag)
	{
		mini->before = ft_before(mini->args[i]);
		mini->after = ft_after(mini->args[i]);
	}
	else
	{
		free(mini->before);
		free(mini->after);
	}
}