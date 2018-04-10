/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:49:38 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:49:42 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wild_format(char *cpy, t_print *elem)
{
	char *str;
	char *ptr;

	ptr = NULL;
	if (!(str = ft_strnew(1)))
		return (NULL);
	str[0] = *(cpy + elem->next - 1);
	if (elem->width)
	{
		if (!(ptr = ft_strnew(elem->width - 1)))
			return (NULL);
		ft_memset(ptr, ' ', elem->width - 1);
		if (elem->minus)
			str = ft_join_and_free_all(str, ptr);
		else
			str = ft_join_and_free_all(ptr, str);
	}
	elem->len = ft_strlen(str);
	return (str);
}

char	*ft_cutter(char *format, t_print *elem)
{
	elem->len = ft_strlen(format);
	return (ft_strdup(format));
}

char	*ft_freezer(char *str)
{
	free(str);
	return (NULL);
}
