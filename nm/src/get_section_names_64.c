#include "nm.h"

static long			get_nb_sects(struct load_command *lc, uint32_t ncmds)
{
	struct segment_command_64	*seg;
	uint32_t					i;
	uint32_t					nb_sections;

	nb_sections = 0;
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (check_addr((void**)&seg, (void*)lc, sizeof(*seg)) != 0)
				return (-1);
			nb_sections += seg->nsects;
		}
		if (check_addr((void**)&lc, (void*)lc + lc->cmdsize, sizeof(*lc)) != 0)
			return (-1);
		i++;
	}
	return (nb_sections);
}

char			**get_section_names_64(struct load_command *lc)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	uint32_t					i;
	uint32_t					n;
	long						nb_sect;
	char						**sections_name;

	if ((nb_sect = get_nb_sects(lc, ((struct mach_header_64 *)lc)->ncmds)) == -1)
		return (NULL);
	if (!(sections_name = (char**)ft_memalloc(sizeof(char*) * (nb_sect + 1))))
		return (NULL);
	i = 0;
	while (i < nb_sect)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)((void*)seg + sizeof(*seg));
			n = -1;
			while (++n < seg->nsects)
			{
				sections_name[i++] = sec->sectname;
				//sec = (void*)sec + sizeof(*sec);
				if (check_addr((void**)&sec, (void*)sec + sizeof(*sec), sizeof(*sec)) != 0)
					return (NULL);
			}
		}
		//lc = (struct load_command*)((void*)lc + lc->cmdsize);
		if (check_addr((void**)&lc, (void*)lc + lc->cmdsize, sizeof(*lc)) != 0)
			return (NULL);
	}
	return (sections_name);
}
