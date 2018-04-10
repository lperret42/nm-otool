/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:10:13 by lperret           #+#    #+#             */
/*   Updated: 2016/11/15 18:45:39 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*copy;
	int		i;

	if (!s || !f)
		return (NULL);
	copy = ft_strnew(ft_strlen(s));
	i = 0;
	if (!copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = (*f)(s[i]);
		i++;
	}
	return (copy);
}
