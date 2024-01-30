/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:54:08 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 13:28:40 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mlc;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	mlc = (char *)malloc((len + 1) * sizeof(char));
	if (!mlc)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mlc[i] = f(i, s[i]);
		i++;
	}
	mlc[i] = '\0';
	return (mlc);
}
