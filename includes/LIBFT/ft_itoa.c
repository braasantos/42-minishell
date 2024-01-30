/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:52:02 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 13:56:14 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getnbr(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count ++;
	}
	return (count);
}

static int	ft_negative(long n)
{
	int	neg_len;

	if (n < 0)
	{
		neg_len = ft_getnbr(n);
		neg_len++;
	}
	else
	{
		neg_len = ft_getnbr(n);
	}
	return (neg_len);
}

static char	*ft_convert(long n, char *str)
{
	int	i;

	i = ft_negative(n);
	if (n == 0)
		str[i - 1] = n + '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		i--;
		str[i] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*mlc;
	long	nbr;
	int		len_nbr;

	nbr = n;
	len_nbr = ft_negative(nbr);
	mlc = (char *)ft_calloc((len_nbr + 1), sizeof(char));
	if (!mlc)
		return (NULL);
	mlc = ft_convert(nbr, mlc);
	mlc[len_nbr] = '\0';
	return (mlc);
}

/*
int main(int argc, char **argv)
{
  if (argc != 2)
    return (0);
  char *num = ft_itoa(atoi(argv[1]));
  printf("%s\n", num);
  free(num);
  //printf("%i\n", ft_negative(nbr));
  return (0);
}*/
