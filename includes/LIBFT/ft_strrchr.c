/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:47:26 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 15:32:53 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;

	ptr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			ptr = s;
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	else
		return ((char *)ptr);
}

/*int main(void)
{
  const char *str = "braulio";
  int c = 'b';
  char *result = ft_strrchr(str, c);
  if (result != NULL)
    printf("%s\n", result);
  else
    printf("not found\n");
  return (0);
}*/

/*int main(void)
{
  const char *str = "braulio";
  int c = '\0';
  char *result = ft_strrchr(str, c);
  if (result != NULL)
  {
    // calcula e imprime a ultima posição do caracter
    int position = result - str;
    printf("Found at position %d\n", position);
  }
  else
  {
    printf("Not found\n");
  }
  return (0);
}*/
