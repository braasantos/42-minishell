/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:00:13 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 13:27:55 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_getnbr(int n, int fd)
{
	if (n >= 10)
	{
		ft_getnbr(n / 10, fd);
		n = n % 10;
	}
	if (n < 10)
	{
		n += 48;
		write(fd, &n, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	ft_getnbr(n, fd);
}
