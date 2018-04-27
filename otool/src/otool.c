/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:08:16 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 17:49:14 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		otool(t_infos infos)
{
	unsigned int	mag;

	if (infos.filesize < 6)
		return (NOT_OBJECT_ERROR);
	mag = *(unsigned int*)(infos.ptr);
	if (mag == MH_MAGIC || mag == MH_MAGIC_64
					|| mag == MH_CIGAM || mag == MH_CIGAM_64)
	{
		infos.nbits = (mag == MH_MAGIC || mag == MH_CIGAM ? 32 : 64);
		infos.swap = (mag == MH_CIGAM || mag == MH_CIGAM_64 ? 1 : 0);
		if (infos.nbfiles >= 1)
			ft_printf("%s:\n", infos.filename);
		return (handle_32_64(infos));
	}
	else if (mag == FAT_MAGIC || mag == FAT_CIGAM ||
			mag == FAT_MAGIC_64 || mag == FAT_CIGAM_64)
	{
		infos.nbits = (mag == FAT_MAGIC || mag == FAT_CIGAM ? 32 : 64);
		infos.swap = (mag == FAT_CIGAM || mag == FAT_CIGAM_64 ? 1 : 0);
		return (handle_fats(infos));
	}
	else if (!ft_strncmp(infos.ptr, ARMAG, SARMAG))
		return (handle_ars(infos));
	else
		return (NOT_OBJECT_ERROR);
}
