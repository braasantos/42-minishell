/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braasantos <braasantos@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:51:06 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/09 20:01:58 by braasantos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

{
	int		len;
	int		i;
	char	*mlc;

	len = ft_strlen(s);
	mlc = (char *)malloc ((len + 1) * sizeof(char));
	if (!mlc)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mlc[i] = s[i];
		i++;
	}
	mlc[i] = '\0';
	return (mlc);
}
/*int	main(void)
{
  char	a[] = "braulio";
  printf("Duplicate str: %s", ft_strdup(a));
  return (0);
}*/
