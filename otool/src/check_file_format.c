/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:28:34 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 17:51:53 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int			check(void **dst, void *src, size_t size, t_infos infos)
{
	if (!(src >= (void*)infos.ptr && src <= (void*)infos.ptr + infos.filesize &&
		src + size >= (void*)infos.ptr &&
						src + size <= (void*)infos.ptr + infos.filesize))
		return (-1);
	if (dst != NULL)
		*dst = src;
	return (0);
}
