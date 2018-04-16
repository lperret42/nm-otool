#include "nm.h"

char		secto(char *name)
{
	if (!ft_strcmp(name, SECT_DATA))
		return ('D');
	else if (!ft_strcmp(name, SECT_BSS))
		return ('B');
	else if (!ft_strcmp(name, SECT_TEXT))
		return ('T');
	else
		return ('S');
}

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
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}
/*
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
*/
t_sym		get_sym(char for_debug, unsigned long value, int n_sect, char letter, char *name)
{
	t_sym		sym;

	if (DEBUG)
	{
		ft_printf("n_sect: %d\n", n_sect);
		ft_printf("name: %s\n", name);
	}
	sym.for_debug = for_debug;
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
		if (syms[i].name && !syms[i].for_debug)
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
		section_name = symbol.n_sect == NO_SECT ? NULL : sections_name[symbol.n_sect - 1];
		letter = typing(symbol.n_type, symbol.n_sect, section_name);
		syms[i] = get_sym(symbol.n_type & N_STAB ? 1 : 0, symbol.n_value,
				symbol.n_sect, letter, stringtable + symbol.n_un.n_strx);
		i++;
	}
	return syms;
}

char		**get_sections_name(struct load_command *lc, uint32_t nb_sections)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	uint32_t					i;
	uint32_t					n;
	char						**sections_name;

	if (!(sections_name = (char**)ft_memalloc(sizeof(char*) * (nb_sections + 1))))
		return NULL;
	i = 0;
	while (i < nb_sections)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)((void*)seg + sizeof(*seg));
			n = -1;
			while (++n < seg->nsects)
			{
				sections_name[i++] = sec->sectname;
				sec = (void*)sec + sizeof(*sec);
			}
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
	}
	return sections_name;
}

uint32_t	get_nb_sections(struct load_command *lc, uint32_t ncmds)
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
			seg = (struct segment_command_64 *)lc;
			nb_sections += seg->nsects;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	return (nb_sections);
}

void		handle_64(char *ptr, t_options options)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	char					**sections_name;
	t_sym					*syms;

	header = (struct mach_header_64 *)ptr;
	lc = (struct load_command *)(ptr + sizeof(*header));
	sections_name = get_sections_name(lc, get_nb_sections(lc, header->ncmds));
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			syms = get_syms(((struct symtab_command *)lc)->nsyms,
				((struct symtab_command *)lc)->symoff,
				((struct symtab_command *)lc)->stroff, ptr, sections_name);
			//quick_sort_syms_numerically(syms, 0, sym->nsyms - 1);
			if (!options.order)
			{
				quick_sort_syms_ascii(syms, 0, ((struct symtab_command *)lc)->nsyms - 1);
				quick_sort_syms_same_ascii_numerically(syms, ((struct symtab_command *)lc)->nsyms);
			}
			print_syms(syms, ((struct symtab_command *)lc)->nsyms);
			free(syms);
			//break;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	free(sections_name);
}
