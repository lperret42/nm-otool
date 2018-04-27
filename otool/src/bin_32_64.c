/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_32_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:50:07 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 17:50:25 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int		handle_sect_text(void *sec, t_infos infos)
{
	uint32_t	addr_32;
	uint64_t	addr_64;
	uint32_t	size_32;
	uint64_t	size_64;
	uint32_t	offset;

	if (infos.nbits == 32)
	{
		addr_32 = swap32(((t_sec*)sec)->addr, infos.swap);
		size_32 = swap32(((t_sec*)sec)->size, infos.swap);
		offset = swap32(((t_sec*)sec)->offset, infos.swap);
		if (check(NULL, (void*)infos.ptr + offset, size_32, infos) != 0)
			return (FORMAT_ERROR);
		print_text_sec_32(addr_32, size_32, (void*)infos.ptr + offset, infos);
	}
	else
	{
		addr_64 = swap64(((t_sec_64*)sec)->addr, infos.swap);
		size_64 = swap64(((t_sec_64*)sec)->size, infos.swap);
		offset = swap32(((t_sec_64*)sec)->offset, infos.swap);
		if (check(NULL, (void*)infos.ptr + offset, size_64, infos) != 0)
			return (FORMAT_ERROR);
		print_text_sec_64(addr_64, size_64, (void*)infos.ptr + offset, infos);
	}
	return (0);
}

static int		loop_nsects(void *sec, uint32_t sec_size, t_infos infos)
{
	char		*sectname;
	uint32_t	sectname_size;
	char		*segname;
	uint32_t	segname_size;
	uint32_t	i;

	i = 0;
	while (i < infos.nsects)
	{
		sectname = (infos.nbits == 32 ? ((t_sec*)sec)->sectname :
													((t_sec*)sec)->sectname);
		sectname_size = sizeof((infos.nbits == 32 ? ((t_sec*)sec)->sectname :
													((t_sec*)sec)->sectname));
		segname = (infos.nbits == 32 ? ((t_sec*)sec)->segname :
													((t_sec*)sec)->segname);
		segname_size = sizeof((infos.nbits == 32 ? ((t_sec*)sec)->segname :
													((t_sec*)sec)->segname));
		if (!ft_strncmp(sectname, SECT_TEXT, sectname_size) &&
					!ft_strncmp(segname, SEG_TEXT, segname_size))
			if (handle_sect_text(sec, infos) != 0)
				return (FORMAT_ERROR);
		sec += sec_size;
		i++;
	}
	return (0);
}

static int		handle_lc_segment(void *seg, t_infos infos)
{
	uint32_t			seg_size;
	uint32_t			sec_size;

	seg_size = (infos.nbits == 32 ? sizeof(t_seg_com) : sizeof(t_seg_com_64));
	if (check(NULL, seg, seg_size, infos) != 0)
		return (FORMAT_ERROR);
	infos.nsects = swap32(infos.nbits == 32 ? ((t_seg_com *)seg)->nsects :
				((t_seg_com_64*)seg)->nsects, infos.swap);
	sec_size = (infos.nbits == 32 ? sizeof(t_sec) : sizeof(t_sec_64));
	if (check(NULL, seg + seg_size, infos.nsects * sec_size, infos) != 0)
		return (FORMAT_ERROR);
	return (loop_nsects(seg + seg_size, sec_size, infos));
}

static int		get_data(t_infos *infos)
{
	uint32_t	header_size;

	header_size = (infos->nbits == 32 ? sizeof(t_header) : sizeof(t_header_64));
	if (check(NULL, infos->ptr, header_size, *infos) != 0)
		return (FORMAT_ERROR);
	infos->ncmds = (infos->nbits == 32 ?
			swap32(((t_header*)(infos->ptr))->ncmds, infos->swap) :
			swap32(((t_header_64*)(infos->ptr))->ncmds, infos->swap));
	infos->lc = (void*)infos->ptr + header_size;
	return (0);
}

int				handle_32_64(t_infos infos)
{
	int						error;
	uint32_t				i;
	uint32_t				cmd;

	error = get_data(&infos);
	if (error != NO_ERROR)
		return (error);
	i = 0;
	while (i < infos.ncmds)
	{
		if (check(NULL, infos.lc, sizeof(struct load_command), infos) != 0)
			return (FORMAT_ERROR);
		cmd = swap32(infos.lc->cmd, infos.swap);
		if (cmd == (infos.nbits == 32 ? LC_SEGMENT : LC_SEGMENT_64))
			if ((error = handle_lc_segment((void*)infos.lc, infos)) != 0)
				return (error);
		infos.lc = (void*)infos.lc + swap32(infos.lc->cmdsize, infos.swap);
		i++;
	}
	return (0);
}
