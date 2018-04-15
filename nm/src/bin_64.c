#include "nm.h"

char		secto(char *name)
{
	/*
	ft_printf("name: %s\n", name);
	ft_printf("SECT_DATA: %s\n", SECT_DATA);
	ft_printf("SECT_BSS: %s\n", SECT_BSS);
	ft_printf("SECT_TEXT: %s\n", SECT_TEXT);
	*/
	if (!ft_strcmp(name, SECT_DATA))
		return ('D');
	else if (!ft_strcmp(name, SECT_BSS))
		return ('B');
	else if (!ft_strcmp(name, SECT_TEXT))
		return ('T');
	else
		return ('S');
}

//char		typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr)
char		typing(uint32_t type, int n_value, char *section_name)
{
	char	ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (n_value)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = secto(section_name);
		//ret = 'Z';   // to handle later
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

char	get_n_type(int n_type, int n_sect)
{
	if (n_sect != NO_SECT)
		return 'T';
	if (n_type == N_UNDF)
		return 'U';
	else if (n_type == N_ABS)
		return 'A';
	else					//need to handle this case
		return 'A';   
}

t_sym		get_sym(unsigned long value, int n_sect, char letter, char *name)
{
	t_sym		sym;

	if (DEBUG)
		ft_printf("n_sect: %d\n", n_sect);
	sym.value = value;
	sym.n_sect = n_sect;
	sym.letter = letter;
	sym.name = name;

	return sym;
}

void		print_syms(t_sym *syms, int nsyms)
{
	int		i;

	i = 0;
	while (i < nsyms)
	{
		if (syms[i].name)
		{
			if (syms[i].n_sect != NO_SECT)
				ft_printf("%016lx", syms[i].value);
			else
				ft_printf("%s", "                ");
			ft_printf(" ");
			ft_printf("%c", syms[i].letter);
			ft_printf(" ");
			ft_printf("%s\n", syms[i].name);
		}
		i++;
	}
}

t_sym		*get_syms(int nsyms, int symoff, int stroff, char *ptr, char **sections_name)
{
	int					i;
	t_sym				*syms;
	struct nlist_64		*array;
	char				*stringtable;
	struct nlist_64		symbol;
	char				*section_name;
	char				letter;

	if (!(syms = (t_sym*)ft_memalloc(sizeof(t_sym) * nsyms)))
		return NULL;
	array = (struct nlist_64 *)(ptr + symoff);
	stringtable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		symbol = array[i];
		if (!(symbol.n_type & N_STAB))    //not symbolic debugging entry
		{
			section_name = symbol.n_sect == NO_SECT ? NULL : sections_name[symbol.n_sect - 1];
			//letter = get_n_type(symbol.n_type & N_TYPE, symbol.n_sect);
			letter = typing(symbol.n_type, symbol.n_sect,
				section_name);
			syms[i] = get_sym(symbol.n_value, symbol.n_sect, letter,
									stringtable + symbol.n_un.n_strx);
		}
		i++;
	}
	return syms;
}

void		print_secs_of_a_seg(struct segment_command_64 *seg)
{
	if (!DEBUG)
		return ;
	return ;
	struct	section_64	*sec;
	unsigned int		i;

	sec = (struct section_64 *)((void*)seg + sizeof(*seg));
	i = 0;
	while (i < seg->nsects)
	{
		ft_printf("sec->sectname: %s\n", sec->sectname);
		sec = (void*)sec + sec->size;
		i++;
	}
}

char		**get_sections_name(struct load_command *lc, uint32_t ncmds)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	uint32_t					i;
	uint32_t					n;
	uint32_t					nb_sections;
	char						**sections_name;
	struct load_command			*lc_copy;

	lc_copy = lc;
	nb_sections = 0;
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			nb_sections += seg->nsects;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	if (DEBUG)
		ft_printf("nb_sections: %u\n", nb_sections);
	if (!(sections_name = (char**)ft_memalloc(sizeof(char*) * (nb_sections + 1))))
		return NULL;
	lc = lc_copy;
	i = 0;
	while (i < nb_sections)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)((void*)seg + sizeof(*seg));
			n = 0;
			if (DEBUG)
				ft_printf("seg->nsects %u\n", seg->nsects);
			while (n < seg->nsects)
			{
				if (DEBUG)
					ft_printf("sec->sectname: %s\n", sec->sectname);
				sections_name[i] = sec->sectname;
				sec = (void*)sec + sizeof(*sec);
				i++;
				n++;
			}
			if (DEBUG)
				ft_printf("n: %u\n", n);
		}
		/*if (i >= nb_sections - 1)
			break;          // need to change, really dirty*/
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
	}
	return sections_name;
}


void		handle_64(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	char					**sections_name;
	struct segment_command_64	*seg;
	
	struct symtab_command	*sym;
	t_sym					*syms;

	header = (struct mach_header_64 *)ptr;
	if (DEBUG == 1)
	{
		ft_printf("header->magic: %#x\n", header->magic);
		ft_printf("header->cputype: %d\n", header->cputype);
		ft_printf("header->cpusubtype: %d\n", header->cpusubtype);
		ft_printf("header->filetype: %d\n", header->filetype);
		ft_printf("header->ncmds: %d\n", header->ncmds);
		ft_printf("header->sizeofcmds: %d\n", header->sizeofcmds);
		ft_printf("header->flags: %#x\n", header->flags);
		ft_printf("header->reserved: %d\n", header->reserved);
	}
	ncmds = header->ncmds;
	lc = (struct load_command *)(ptr + sizeof(*header));
	i = 0;

	sections_name = get_sections_name(lc, header->ncmds);
	while (i < ncmds)
	{
		if (DEBUG == 1)
		{
			ft_printf("lc->cmd: %u\n", lc->cmd);
			ft_printf("lc->cmdsize: %u\n", lc->cmdsize);
		}
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (DEBUG == 1)
			{
				ft_printf("sym->nsyms: %d\n", sym->nsyms);
				ft_printf("sym->symoff: %d\n", sym->symoff);
				ft_printf("sym->stroff: %d\n", sym->stroff);
				ft_printf("sym->strsize: %d\n", sym->strsize);
			}
			syms = get_syms(sym->nsyms, sym->symoff, sym->stroff, ptr, sections_name);
			//quick_sort_syms_numerically(syms, 0, sym->nsyms - 1);
			quick_sort_syms_ascii(syms, 0, sym->nsyms - 1);
			quick_sort_syms_same_ascii_numerically(syms, sym->nsyms);
			print_syms(syms, sym->nsyms);
			free(syms);
			//break;
		}
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			if (DEBUG)
			{
				ft_printf("************segment_command_64************\n");
				ft_printf("seg->segname: %s\n", seg->segname);
				ft_printf("seg->nsects: %d\n", seg->nsects);
				print_secs_of_a_seg(seg);
				ft_printf("***********end segment_command_64*********\n");
			}
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	free(sections_name);
}
