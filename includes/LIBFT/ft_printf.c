/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:20:23 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/17 13:39:59 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_checkformat(va_list args, const char *format, int *count)
{
	if (*format == 'c')
		ft_put_char(va_arg(args, int), count);
	if (*format == 'd' || *format == 'i')
		ft_put_nbr(va_arg(args, int), count);
	if (*format == 's')
		ft_put_str(va_arg(args, char *), count);
	if (*format == 'u')
		ft_putunsig(va_arg(args, unsigned int), count);
	if (*format == 'X' || *format == 'x')
		ft_puthexa(va_arg(args, int), format, count);
	if (*format == 'p')
		ft_putadress(va_arg(args, size_t), count);
	if (*format == '%')
		ft_put_char('%', count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start (args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ft_checkformat(args, format, &count);
		}
		else
		{
			write(1, format, 1);
			count += 1;
		}
		format++;
	}
	va_end(args);
	return (count);
}
