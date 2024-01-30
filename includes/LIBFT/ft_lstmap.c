/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:19:06 by bjorge-m          #+#    #+#             */
/*   Updated: 2023/10/12 19:34:52 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		curr = ft_lstnew(lst->content);
		if (!curr)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		curr->content = (f)(lst->content);
		ft_lstadd_back(&head, curr);
		lst = lst->next;
	}
	return (head);
}
