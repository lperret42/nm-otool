/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:55:38 by lperret           #+#    #+#             */
/*   Updated: 2016/11/17 22:33:54 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	size;

	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	if (i == ft_strlen(s))
		size = 0;
	else
		size = j - i + 1;
	if (!(new = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	k = -1;
	while (++k < size)
		new[k] = s[i + k];
	new[k] = '\0';
	return (new);
}
