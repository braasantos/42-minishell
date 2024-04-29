/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:25:54 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 10:25:55 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	fputstr(char *str, int *count, int fd)
{
	if (!str)
	{
		*count += write(fd, "(null)", 6);
		return ;
	}
	while (*str)
	{
		write(fd, str, 1);
		*count += 1;
		str++;
	}
}

static void	fcheckformat(va_list args, const char *format, int *count, int fd)
{
	if (*format == 's')
		fputstr(va_arg(args, char *), count, fd);
}

int	ft_fprintf(int fd, const char *format, ...)
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
			fcheckformat(args, format, &count, fd);
		}
		else
		{
			write(fd, format, 1);
			count += 1;
		}
		format++;
	}
	va_end(args);
	return (count);
}
