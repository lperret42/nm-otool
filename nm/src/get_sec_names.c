#include "nm.h"

static long			get_nb_sects(struct load_command *lc, uint32_t ncmds)
{
	uint32_t					i;
	size_t						tmp;
	uint32_t					nb_sections;

	if (DEBUG)
		ft_printf("in get_nb_sects, ncmds = %u\n", ncmds);
	nb_sections = 0;
	i = 0;
	while (i < ncmds)
	{
		if (DEBUG)
			ft_printf("in get_nb_sects, i = %u\n", i);
		if (lc->cmd == (glob()->nbits == 32 ? LC_SEGMENT : LC_SEGMENT_64))
		{
			tmp = (glob()->nbits == 32 ? sizeof(seg_com) : sizeof(seg_com_64));
			if (check_addr(NULL, (void*)lc, tmp) != 0)
				return (-1);
			if (glob()->nbits == 32)
				nb_sections += ((seg_com *)lc)->nsects;
			else
				nb_sections += ((seg_com_64 *)lc)->nsects;
		}
		if (check_addr((void**)&lc, (void*)lc + lc->cmdsize, sizeof(*lc)) != 0)
			return (-1);
		i++;
	}
	return (nb_sections);
}

int				get_sec_names(struct load_command *lc, uint32_t ncmds)
{
	uint32_t					i;
	uint32_t					n;
	size_t						tmp;
	long						nb_sect;

	if ((nb_sect = get_nb_sects(lc, ncmds)) == -1)
		return (-1);
	if (DEBUG)
		ft_printf("in get_sec_names, nb_sect = %ld\n", nb_sect);
	if (!(glob()->sec_names = (char**)ft_memalloc(sizeof(char*) * (nb_sect + 1))))
		return (0);
	i = 0;
	while (i < nb_sect)
	{
		if (DEBUG)
			ft_printf("in get_sec_names, i = %u\n", i);
		if (lc->cmd == (glob()->nbits == 32 ? LC_SEGMENT : LC_SEGMENT_64))
		{
			n = -1;
			if (DEBUG)
			{
				ft_printf("nombre: %u\n", glob()->nbits == 32 ? ((seg_com *)lc)->nsects :
								((seg_com_64 *)lc)->nsects);
				ft_printf("comp: %d\n", (uint32_t)1 < (glob()->nbits == 32 ? ((seg_com *)lc)->nsects :
								((seg_com_64 *)lc)->nsects));
			}
			while (++n < (glob()->nbits == 32 ? ((seg_com *)lc)->nsects :
								((seg_com_64 *)lc)->nsects))
			{
				if (DEBUG)
					ft_printf("in get_sec_names boucle on n\n");
				if (DEBUG)
					ft_printf("n: %u\n", n);
				glob()->sec_names[i++] = (glob()->nbits == 32 ? ((struct section *)((void*)lc + sizeof(seg_com)) + n)->sectname :
					((struct section_64 *)((void*)lc + sizeof(seg_com_64)) + n)->sectname);
				tmp = (glob()->nbits == 32 ? sizeof(struct section) : sizeof(struct section_64));
				if (DEBUG)
					ft_printf("tmp: %lu\n", tmp);
				if (check_addr(NULL, (void*)lc + tmp * n, tmp) != 0)
					return (-1);
			}
		}
		if (check_addr((void**)&lc, (void*)lc + lc->cmdsize, sizeof(*lc)) != 0)
			return (-1);
	}
	if (DEBUG)
	{
		int		a = 0;
		while (glob()->sec_names[a])
			ft_printf("sec_names[a]: %s\n", glob()->sec_names[a++]);
	}
	return (0);
}
