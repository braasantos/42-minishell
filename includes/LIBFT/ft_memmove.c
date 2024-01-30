/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:41:24 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 16:55:51 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (dest > src)
	{
		while (i < n)
		{
			*((char *)dest + n - 1) = *((char *)src + n - 1);
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			*((char *)dest + i) = *((char *)src + i);
			i++;
		}
	}
	return (dest);
}

/*int main() {
    char source[] = "Hello, World!";
    char destination[20];  // Make sure there's enough space for the copy

    // Test copying forward (no overlap)
    ft_memmove(destination, source, 6);
    printf("After ft_memmove (forward): %s\n", destination);

    // Test copying backward (with overlap)
    //ft_memmove(destination + 7, destination, 7);
    //printf("After ft_memmove (backward): %s\n", destination);
		
		//memmove(destination, source, 6);
		//printf("%s\n", destination);
    return 0;
}*/
