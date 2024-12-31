/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:49:31 by thashimo          #+#    #+#             */
/*   Updated: 2023/10/29 18:43:23 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*newlst;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	head = NULL;
	while (current != NULL)
	{
		newlst = ft_lstnew((*f)(current -> content));
		if (!newlst)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, newlst);
		current = current -> next;
	}
	return (head);
}
