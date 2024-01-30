/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:44:13 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 19:56:30 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = d_len;
	j = 0;
	if (i >= size || size == 0)
		return (size + s_len);
	while (src[j] && j < size - 1 - i)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (d_len + s_len);
}
/*int main(void)
{
    char s1[22] = "Hello";
    char s2[] = "World!";

 printf("%zu", ft_strlcat(s1, s2, 6));
}*/
