/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:57:13 by lperret           #+#    #+#             */
/*   Updated: 2016/11/15 16:18:36 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*ptr;

	if (!((new = ft_lstnew(((*f)(lst))->content, ((*f)(lst))->content_size))))
		return (NULL);
	ptr = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(ptr->next = ft_lstnew(((*f)(lst))->content,
						((*f)(lst))->content_size)))
			return (NULL);
		ptr = ptr->next;
	}
	return (new);
}
