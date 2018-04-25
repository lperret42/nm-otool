/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:08:16 by lperret           #+#    #+#             */
/*   Updated: 2018/04/25 14:55:58 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		nm(t_infos infos)
{
	unsigned int	magic_number;

	if (infos.filesize < 6)
		return (NOT_OBJECT_ERROR);
	magic_number = *(unsigned int*)(infos.ptr);
	if (DEBUG)
		ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC || magic_number == MH_MAGIC_64)
	{
		infos.nbits = (magic_number == MH_MAGIC ? 32 : 64);
		if (DEBUG)
			ft_printf("infos.nbits: %d\n", infos.nbits);
		if (infos.nbfiles >= 2)
			ft_printf("\n%s:\n", infos.filename);
		return (handle_32_64(infos));
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		if (DEBUG)
			ft_printf("fat\n");
		return (handle_fats(infos));
	}
	else if (!ft_strncmp(infos.ptr, ARMAG, SARMAG))
		return (handle_ars(infos));
	else
	{
		if (DEBUG)
			ft_printf("not object error\n");
		return (NOT_OBJECT_ERROR);
	}
}
