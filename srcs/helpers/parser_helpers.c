#include "../../inc/minishell.h"

void	pad(char *src, char *dest, int i, int j)
{
	char	skip;

	while (src[i])
	{
		if (src[i] && find_char(src[i], "|><") && !quotes_open(src, i))
		{
			dest[j++] = ' ';
			skip = src[i];
			while (src[i] == skip)
				dest[j++] = src[i++];
			dest[j++] = ' ';
			continue ;
		}
		dest[j++] = src[i];
		i++;
	}
}

int	padding_needed(char *str, int i, int pad)
{
	char	skip;

	while (str[i])
	{
		if (str[i] && find_char(str[i], "|><") && !quotes_open(str, i))
		{
			skip = str[i];
			while (str[i] && str[i] == skip)
				i++;
			pad += 2;
			continue ;
		}
		i++;
	}
	return (pad);
}

char	*pad_central(char *str)
{
	int		extra;
	char	*ret;

	extra = padding_needed(str, 0, 0);
	if (extra == 0)
		return (ft_strdup(str));
	ret = (char *)ft_calloc(1, ft_strlen(str) + extra + 1);
	pad(str, ret, 0, 0);
	return (ret);
}

int check_position_bool(t_mini *mini, char *to_find)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], to_find))
			return i;
		i++;
	}
	return 0;
}

int check_position(t_mini *mini, int j)
{
	int i;

	i = 0;
	while (mini->args[i])
	{
		if (!ft_strcmp(mini->args[i], mini->args[j]))
			return i;
		i++;
	}
	return 0;
}