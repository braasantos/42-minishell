/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:59:35 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 15:02:01 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mal;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start > s_len)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	mal = (char *)malloc((len + 1) * sizeof(char));
	if (!mal)
		return (NULL);
	i = 0;
	while (i < len)
	{
		mal[i] = s[start + i];
		i++;
	}
	mal[i] = '\0'; 
	return (mal);
}
