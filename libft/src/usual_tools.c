/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usual_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:50:26 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:50:31 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndcpy(char *dst, char *src)
{
	char *ret_d;
	char *ret_s;

	dst = dst - (ft_strlen(src) - 1);
	ret_d = dst;
	ret_s = src;
	if (dst && src && (ft_strlen(dst) >= ft_strlen(src)))
		while (*src)
			*dst++ = *src++;
	free(ret_s);
	return (ret_d);
}

char	*ft_join_memory_free_some(char *s1, char *s2, t_print *elem)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s2);
	if (!(ptr = ft_memalloc(len + elem->len + 1)))
		return (NULL);
	ft_memcpy(ptr, s1, elem->len);
	ft_memcpy(ptr + elem->len, s2, len);
	elem->len += len;
	if (s1)
		free(s1);
	return (ptr);
}

char	*ft_join_memory_free_all(char *s1, char *s2, t_print *elem)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1);
	if (!(ptr = ft_memalloc(len + elem->len)))
		return (NULL);
	ft_memcpy(ptr, s1, len);
	ft_memcpy(ptr + len, s2, elem->len);
	elem->len += len;
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ptr);
}

char	*ft_join_memory_free_all_bis(char *s1, char *s2, size_t size,
		t_print *elem)
{
	char	*ptr;

	if (!(ptr = ft_memalloc(size + elem->len)))
		return (NULL);
	ft_memcpy(ptr, s1, size);
	ft_memcpy(ptr + size, s2, elem->len);
	elem->len += size;
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ptr);
}

char	*ft_join_and_free_all(char *s1, char *s2)
{
	char *ptr;

	if (!(ptr = ft_strjoin(s1, s2)))
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (NULL);
	}
	free(s1);
	free(s2);
	return (ptr);
}
