#include "../../inc/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	just_print(void)
{
	g_signal = 2;
	ft_fprintf(2, " syntax error near unexpected token `newline'\n");
}

int	count_red_pipe(t_mini *mini)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
			count++;
		if (!ft_strcmp(mini->args[i], "<"))
			count++;
		if (!ft_strcmp(mini->args[i], ">>"))
			count++;
		if (!ft_strcmp(mini->args[i], "|"))
			count++;
		i++;
	}
	return (count);
}

int	im_done_parser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">") || !ft_strcmp(mini->args[i], "<"))
		{
			if (mini->args[i + 1])
			{
				if (check_options(mini->args[i + 1]))
				{
					g_signal = 2;
					ft_fprintf(2, " syntax error near unexpected token `%s'\n", mini->args[i + 1]);
					return (1);
				}
			}
			else
			{
				return (just_print(), 1);
			}

		}
		i++;
	}
	return (0);
}

int	red_out(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], ">"))
			return (1);
        if (!ft_strcmp(mini->args[i], ">>"))
			return (1);
		i++;
	}
	return (0);
}