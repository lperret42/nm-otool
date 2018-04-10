/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:49:32 by lperret           #+#    #+#             */
/*   Updated: 2016/11/14 18:07:04 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*modify;

	modify = s1;
	while (*modify)
		modify++;
	while (*s2 && n > 0)
	{
		*modify++ = *s2++;
		n--;
	}
	*modify = '\0';
	return (s1);
}
