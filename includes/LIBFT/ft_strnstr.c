/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:30 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 19:56:04 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (len == 0 && big == NULL)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j < len))
		{
			if (little[j + 1] == '\0')
			{
				return ((char *)(big + i));
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
/*int main()
{
    char *haystack = "i am batman and im the shadows";
    char *needle = "b";
    char *location;
    char *loca;

    location = strstr(haystack,needle);
    if(location == NULL)
        puts("Unable to find string with strstr().");
    else
        printf("strstr() found '%s' in '%s'.\n",
            needle,
            haystack);
    loca = ft_strstr(haystack,needle, 10);
    if(loca == NULL)
        puts("Unable to find string with strstr().");
    else
        printf("strstr() found '%s' in '%s'.\n",
            needle,
            haystack);

    return(0);
}*/
