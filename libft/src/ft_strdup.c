/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 09:45:33 by lperret           #+#    #+#             */
/*   Updated: 2016/11/17 22:34:12 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;

	if (!(copy = (char *)malloc(sizeof(*copy) * (ft_strlen(s1) + 1))))
		return (NULL);
	return (ft_strcpy(copy, s1));
}
