/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:19:16 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/02 15:05:22 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_str(char *str, int *count)
{
	if (!str)
	{
		*count += write(1, "(null)", 6);
		return ;
	}
	while (*str)
	{
		write(1, str, 1);
		*count += 1;
		str++;
	}
}
/*int main (void)
{
  char *b = "teste 1234 teste";
  put_str(b);
}*/
