/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:08:13 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/02 14:30:31 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_getadress(size_t n, int *count)
{
	char	*hexalow;

	hexalow = "0123456789abcdef";
	if (n >= 16)
		ft_getadress(n / 16, count);
	*count += write(1, &hexalow[n % 16], 1);
}

void	ft_putadress(size_t nbr, int *count)
{
	if (!nbr)
	{
		*count += write(1, "(nil)", 5);
		return ;
	}
	*count += write(1, "0x", 2);
	ft_getadress(nbr, count);
}
