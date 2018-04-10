/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:04:35 by lperret           #+#    #+#             */
/*   Updated: 2016/11/14 16:32:09 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*modify;

	modify = s1;
	while (*modify)
		modify++;
	while (*s2)
		*modify++ = *s2++;
	*modify = '\0';
	return (s1);
}
