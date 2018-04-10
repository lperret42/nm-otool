/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:01:36 by lperret           #+#    #+#             */
/*   Updated: 2016/11/15 16:50:52 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	to_find;
	unsigned char	*ptr_s;

	to_find = (unsigned char)c;
	ptr_s = (unsigned char*)s;
	while (n--)
	{
		if (*ptr_s == to_find)
			return ((void*)ptr_s);
		ptr_s++;
	}
	return (NULL);
}
