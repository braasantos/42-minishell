#include "../../inc/minishell.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


int fore(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (s[i] == ' ')
		i++;
	return (i);
}

int afta(char *s)
{
	int j;
	int i;

	j = 0;
	i = fore(s);
	while (s[i++] && s[i] != '=')
		j++;
	if (s[i++] == '=')
		j++;
	return (j);
}

char *help(char *str)
{
	int i;
	int j;
	int k;
	char *s;

	j = afta(str);
	s = malloc(sizeof(char) * (j + 2));
	k = fore(str);
	i = 0;
	while (str[k])
	{
		s[i++] = str[k];
		k++;
	}
	s[j] = '=';
	s[j + 1] = '\0';
	return (s);
}