/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:56:44 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 19:57:54 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*b;

	b = malloc(nmemb * size);
	if (!b) 
		return (NULL);
	else 
		ft_bzero(b, nmemb * size);
	return (b);
}
