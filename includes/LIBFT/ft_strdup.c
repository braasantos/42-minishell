/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:51:06 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/10 18:03:25 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
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
