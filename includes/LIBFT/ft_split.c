/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:08:10 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 15:16:12 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else
		{
			if (!flag)
			{
				count++;
				flag = 1;
			}
		}
		s++;
	}
	return (count);
}

int	ft_free(char **new_arr, int count)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < count)
		if (!new_arr[i++])
			flag = 1;
	if (flag)
	{
		i = 0;
		while (i < count)
			free(new_arr[i++]);
		free(new_arr);
		return (0);
	}
	return (1);
}

static char	**ft_putwords(char **new, char const *s, char c)
{
	char	**newarr;
	int		flag;
	int		count;

	newarr = new; 
	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else
		{
			if (!flag)
			{
				newarr[count] = ft_substr(s, 0, ft_strchr(s, c) - s);
				flag = 1;
				count++;
			}
		}
		s++;
	}
	newarr[count] = NULL;
	return (newarr);
}

char	**ft_split(char const *s, char c)
{
	char	**new_arr;
	int		count;

	if (!s)
		return (NULL);
	count = ft_countword(s, c);
	new_arr = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!new_arr)
		return (NULL);
	ft_putwords(new_arr, s, c);
	if (!ft_free(new_arr, count))
		return (NULL);
	return (new_arr);
}
/*int main(void)
{
    char const *s = "isso e um teste para ver se a split funciona";
    char c = ' ';
    
    char **result = ft_split(s, c);
 if (result) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("array : %s\n", result[i]);
            free(result[i]); // Liberar a memória alocada para cada palavra
        }
        free(result); // Liberar a memória alocada para o array de strings
    } else {
        // Trate a falha na alocação de memória aqui
    }

    return 0;
}*/
