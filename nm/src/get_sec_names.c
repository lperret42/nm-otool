/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sec_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:38:38 by lperret           #+#    #+#             */
/*   Updated: 2018/04/26 17:50:18 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static long			get_nb_sects(struct load_command *lc,
									uint32_t ncmds, t_infos *infos)
{
	uint32_t					i;
	uint32_t					nb_sections;

	nb_sections = 0;
	i = 0;
	while (i < ncmds)
	{
		if (swap32(lc->cmd, infos->swap) == (infos->nbits == 32 ?
											LC_SEGMENT : LC_SEGMENT_64))
		{
			if (check(NULL, (void*)lc, (infos->nbits == 32 ?
					sizeof(t_seg_com) : sizeof(t_seg_com_64)), *infos) != 0)
				return (-1);
			if (infos->nbits == 32)
				nb_sections += swap32(((t_seg_com *)lc)->nsects, infos->swap);
			else
				nb_sections += swap32(((t_seg_com_64 *)lc)->nsects,
															infos->swap);
		}
		if (check((void**)&lc, (void*)lc +
				swap32(lc->cmdsize, infos->swap), sizeof(*lc), *infos) != 0)
			return (-1);
		i++;
	}
	return (nb_sections);
}

static int			get_sec_names_32(struct load_command *lc, long nb_sect,
															t_infos *infos)
{
	uint32_t					i;
	uint32_t					n;
	size_t						tmp;

	tmp = sizeof(struct section);
	i = 0;
	while (i < nb_sect)
	{
		if (swap32(lc->cmd, infos->swap) == LC_SEGMENT)
		{
			n = 0;
			while (n < swap32(((t_seg_com *)lc)->nsects, infos->swap))
			{
				infos->sec_names[i++] = ((struct section *)((void*)lc +
										sizeof(t_seg_com)) + n)->sectname;
				if (check(NULL, (void*)lc + tmp * n, tmp, *infos) != 0)
					return (-1);
				n++;
			}
		}
		if (check((void**)&lc, (void*)lc +
				swap32(lc->cmdsize, infos->swap), sizeof(*lc), *infos) != 0)
			return (-1);
	}
	return (0);
}

static int			get_sec_names_64(struct load_command *lc, long nb_sect,
															t_infos *infos)
{
	uint32_t					i;
	uint32_t					n;
	size_t						tmp;

	tmp = sizeof(struct section_64);
	i = 0;
	while (i < nb_sect)
	{
		if (swap32(lc->cmd, infos->swap) == LC_SEGMENT_64)
		{
			n = 0;
			while (n < swap32(((t_seg_com_64 *)lc)->nsects, infos->swap))
			{
				infos->sec_names[i++] = ((struct section_64 *)((void*)lc +
										sizeof(t_seg_com_64)) + n)->sectname;
				if (check(NULL, (void*)lc + tmp * n, tmp, *infos) != 0)
					return (-1);
				n++;
			}
		}
		if (check((void**)&lc, (void*)lc +
				swap32(lc->cmdsize, infos->swap), sizeof(*lc), *infos) != 0)
			return (-1);
	}
	return (0);
}

int					get_sec_names(struct load_command *lc, uint32_t ncmds,
														t_infos *infos)
{
	long						nb_sect;

	if ((nb_sect = get_nb_sects(lc, ncmds, infos)) == -1)
		return (FORMAT_ERROR);
	if (!(infos->sec_names = (char**)ft_memalloc(sizeof(char*) *
															(nb_sect + 1))))
		return (0);
	return (infos->nbits == 32 ? get_sec_names_32(lc, nb_sect, infos) :
									get_sec_names_64(lc, nb_sect, infos));
}
