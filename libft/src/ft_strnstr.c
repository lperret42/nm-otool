/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:37:18 by lperret           #+#    #+#             */
/*   Updated: 2016/11/15 19:20:57 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		len_little;

	len_little = ft_strlen(little);
	if (!(*little))
		return ((char*)big);
	while (*big && len-- >= len_little)
	{
		if (ft_memcmp(big, little, len_little) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
