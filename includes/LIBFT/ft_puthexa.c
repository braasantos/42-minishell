/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:13:09 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/01/02 14:30:43 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_gethexa(unsigned int n, const char *format, int*count)
{
	char	*hexalow;
	char	*hexaupp;

	hexalow = "0123456789abcdef";
	hexaupp = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_gethexa(n / 16, format, count);
		n = n % 16;
	}
	if (*format == 'X')
	{
		write(1, &hexaupp[n], 1);
		*count += 1;
		return ;
	}
	write(1, &hexalow[n], 1);
	*count += 1;
}

void	ft_puthexa(unsigned int nbr, const char *format, int *count)
{
	if (nbr == 0)
	{
		write(1, "0", 1);
		*count += 1;
		return ;
	}
	ft_gethexa(nbr, format, count);
}
