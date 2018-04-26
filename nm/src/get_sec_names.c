#include "nm.h"

static long			get_nb_sects(struct load_command *lc,
									uint32_t ncmds, t_infos *infos)
{
	uint32_t					i;
	size_t						tmp;
	uint32_t					nb_sections;

	nb_sections = 0;
	i = 0;
	while (i < ncmds)
	{
		if (swap32(lc->cmd, infos->swap) == (infos->nbits == 32 ?
											LC_SEGMENT : LC_SEGMENT_64))
		{
			tmp = (infos->nbits == 32 ? sizeof(seg_com) : sizeof(seg_com_64));
			if (check_addr(NULL, (void*)lc, tmp, *infos) != 0)
				return (-1);
			if (infos->nbits == 32)
				nb_sections += swap32(((seg_com *)lc)->nsects, infos->swap);
			else
				nb_sections += swap32(((seg_com_64 *)lc)->nsects, infos->swap);
		}
		if (check_addr((void**)&lc, (void*)lc +
				swap32(lc->cmdsize, infos->swap), sizeof(*lc), *infos) != 0)
			return (-1);
		i++;
	}
	return (nb_sections);
}

// need to split in get_sec_names_32 and get_sec_names_64
int				get_sec_names(struct load_command *lc, uint32_t ncmds, t_infos *infos)
{
	uint32_t					i;
	uint32_t					n;
	size_t						tmp;
	long						nb_sect;

	tmp = (infos->nbits == 32 ? sizeof(struct section) : sizeof(struct section_64));
	if ((nb_sect = get_nb_sects(lc, ncmds, infos)) == -1)
		return (-1);
	if (!(infos->sec_names = (char**)ft_memalloc(sizeof(char*) * (nb_sect + 1))))
		return (0);
	i = 0;
	while (i < nb_sect)
	{
		if (swap32(lc->cmd, infos->swap) == (infos->nbits == 32 ? LC_SEGMENT : LC_SEGMENT_64))
		{
			n = -1;
			while (++n < (infos->nbits == 32 ? swap32(((seg_com *)lc)->nsects, infos->swap) :
					swap32(((seg_com_64 *)lc)->nsects, infos->swap)))
			{
				infos->sec_names[i++] = (infos->nbits == 32 ?
					((struct section *)((void*)lc + sizeof(seg_com)) + n)->sectname :
					((struct section_64 *)((void*)lc + sizeof(seg_com_64)) + n)->sectname);
				if (check_addr(NULL, (void*)lc + tmp * n, tmp, *infos) != 0)
					return (-1);
			}
		}
		if (check_addr((void**)&lc, (void*)lc + swap32(lc->cmdsize, infos->swap), sizeof(*lc), *infos) != 0)
			return (-1);
	}
	return (0);
}
