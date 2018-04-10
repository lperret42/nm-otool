/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:41:00 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:41:03 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_set_alpha(t_print *elem, size_t len)
{
	int		nb;
	char	*ret;

	nb = 0;
	if (elem->width > (int)len)
		nb = elem->width - (int)len;
	if (!(ret = ft_strnew(nb)))
		return (NULL);
	ft_memset(ret, ' ', nb);
	return (ret);
}
