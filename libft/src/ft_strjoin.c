/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:42:41 by lperret           #+#    #+#             */
/*   Updated: 2016/11/15 18:51:45 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	char	*begin_concat;

	if (!s1 || !s2)
		return (NULL);
	concat = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!concat)
		return (NULL);
	begin_concat = concat;
	while (*s1)
		*concat++ = *s1++;
	while (*s2)
		*concat++ = *s2++;
	*concat = '\0';
	return (begin_concat);
}
