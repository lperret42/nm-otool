#include "nm.h"

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
		if (syms[i].n_sect != NO_SECT)
			ft_printf("%016x", syms[i].value);
		else
			ft_printf("%s", "                ");
		ft_printf(" ");
		ft_printf("%c", syms[i].letter);
		ft_printf(" ");
		ft_printf("%s\n", syms[i].name);
		i++;
	}
}

t_sym		*get_syms(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	t_sym				*syms;
	struct nlist_64		*array;
	char				*stringtable;
	struct nlist_64		symbol;
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
			letter = get_n_type(symbol.n_type & N_TYPE, symbol.n_sect);
			syms[i] = get_sym(symbol.n_value, symbol.n_sect, letter,
									stringtable + symbol.n_un.n_strx);
		}
		i++;
	}
	return syms;
}

void		handle_64(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
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
		ft_printf("header->flags: %d\n", header->flags);
		ft_printf("header->reserved: %d\n", header->reserved);
	}
	ncmds = header->ncmds;
	lc = (struct load_command *)(ptr + sizeof(*header));
	i = 0;
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
			syms = get_syms(sym->nsyms, sym->symoff, sym->stroff, ptr);
			print_syms(syms, sym->nsyms);
			free(syms);
			break;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
}
