/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:07:30 by lperret           #+#    #+#             */
/*   Updated: 2018/04/26 17:42:44 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		handle_cpu_type(uint32_t cputype, t_infos inf)
{
	if ((cputype & CPU_TYPE_X86_64) == CPU_TYPE_X86_64)
		return (0);
	else if (cputype == CPU_TYPE_I386 && !inf.host_cpu)
	{
		ft_printf("\n%s (for architecture i386):\n", inf.filename);
		return (0);
	}
	else if (cputype == CPU_TYPE_POWERPC && !inf.host_cpu)
	{
		ft_printf("\n%s (for architecture ppc):\n", inf.filename);
		return (0);
	}
	return (-1);
}

static int		handle_fat_32(t_fat_ar *arch, t_infos inf)
{
	t_infos		new_inf;
	uint32_t	cputype;
	uint32_t	offset;
	uint32_t	size;

	cputype = swap32(arch->cputype, inf.swap);
	if (handle_cpu_type(cputype, inf) == -1)
		return (0);
	offset = swap32(arch->offset, inf.swap);
	size = swap32(arch->size, inf.swap);
	if (check(NULL, (void*)inf.ptr + offset, size, inf) != 0)
		return (FORMAT_ERROR);
	ft_memcpy(&new_inf, &inf, sizeof(t_infos));
	new_inf.nbfiles = 0;
	new_inf.ptr = (void*)inf.ptr + offset;
	new_inf.filesize = size;
	new_inf.sec_names = NULL;
	new_inf.syms = NULL;
	return (nm(new_inf));
}

static int		handle_fat_64(t_fat_ar_64 *arch, t_infos inf)
{
	t_infos		new_inf;
	uint32_t	cputype;
	uint32_t	offset;
	uint32_t	size;

	cputype = swap32(arch->cputype, inf.swap);
	if (handle_cpu_type(cputype, inf) == -1)
		return (0);
	offset = swap64(arch->offset, inf.swap);
	size = swap64(arch->size, inf.swap);
	if (check(NULL, (void*)inf.ptr + offset, size, inf) != 0)
		return (FORMAT_ERROR);
	ft_memcpy(&new_inf, &inf, sizeof(t_infos));
	new_inf.nbfiles = 0;
	new_inf.ptr = (void*)inf.ptr + offset;
	new_inf.filesize = size;
	new_inf.sec_names = NULL;
	new_inf.syms = NULL;
	return (nm(new_inf));
}

static int		host(t_infos inf, void *arch,
						uint32_t arch_size, uint32_t nfat_arch)
{
	uint32_t			i;
	uint32_t			cputype;

	i = 0;
	while (i < nfat_arch)
	{
		cputype = swap32(inf.nbits == 32 ?
				((t_fat_ar *)arch)->cputype :
				((t_fat_ar_64 *)arch)->cputype, inf.swap);
		if (cputype == CPU_TYPE_X86_64)
			return (1);
		arch = (void*)arch + arch_size;
		i++;
	}
	return (0);
}

int				handle_fats(t_infos inf)
{
	int					error;
	struct fat_header	*fat;
	void				*ar;
	uint32_t			ar_size;
	uint32_t			i;

	if (check((void**)&fat, inf.ptr, sizeof(*fat), inf) != 0)
		return (FORMAT_ERROR);
	ar = (void*)inf.ptr + sizeof(*fat);
	ar_size = inf.nbits == 32 ? sizeof(t_fat_ar) : sizeof(t_fat_ar_64);
	if (check(NULL, ar, ar_size * swap32(fat->nfat_arch, inf.swap), inf) != 0)
		return (FORMAT_ERROR);
	inf.host_cpu = host(inf, ar, ar_size, swap32(fat->nfat_arch, inf.swap));
	i = -1;
	while (++i < swap32(fat->nfat_arch, inf.swap))
	{
		if ((error = (inf.nbits == 32 ? handle_fat_32((t_fat_ar *)ar, inf) :
			handle_fat_64((t_fat_ar_64 *)ar, inf))) != NO_ERROR)
			return (error);
		if (swap32(inf.nbits == 32 ? ((t_fat_ar *)ar)->cputype :
			((t_fat_ar_64 *)ar)->cputype, inf.swap) == CPU_TYPE_X86_64)
			return (0);
		ar = (void*)ar + ar_size;
	}
	return (0);
}
