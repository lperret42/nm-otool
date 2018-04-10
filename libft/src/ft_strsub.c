/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:53:12 by lperret           #+#    #+#             */
/*   Updated: 2016/11/15 18:48:16 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*copy;

	i = 0;
	if (!s)
		return (NULL);
	copy = ft_strnew(len);
	if (!copy)
		return (NULL);
	while (i < len)
		copy[i++] = s[start++];
	copy[i] = '\0';
	return (copy);
}
