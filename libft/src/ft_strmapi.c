/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:32:09 by lperret           #+#    #+#             */
/*   Updated: 2016/11/15 18:44:20 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*copy;

	i = 0;
	if (!f || !s)
		return (NULL);
	copy = ft_strnew(ft_strlen(s));
	if (!copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = (*f)(i, s[i]);
		i++;
	}
	return (copy);
}
