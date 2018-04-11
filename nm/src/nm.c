#include "nm.h"

void		print_n_type(int n_type, int n_sect)
{
	if (n_sect != NO_SECT)
		ft_printf("T");
	if (n_type == N_UNDF)
		ft_printf("U");
	else if (n_type == N_ABS)
		ft_printf("A");
}

void		print_n_value(int n_value, int n_sect)
{
	if (n_sect != NO_SECT)
		ft_printf("%016x", n_value);
	else
		ft_printf("%s", "                ");
}

void		print_symbol(char *stringtable, struct nlist_64 symbol)
{
	int					n_type;
	int					n_value;

	if (!(symbol.n_type & N_STAB))    //not symbolic debugging entry
	{
		n_type = symbol.n_type & N_TYPE;
		n_value = symbol.n_value;
		print_n_value(n_value, symbol.n_sect);
		ft_printf(" ");
		print_n_type(n_type, symbol.n_sect);
		ft_printf(" ");
		ft_printf("%s", stringtable + symbol.n_un.n_strx);
		if (DEBUG == 1)
		{
			ft_printf("   n_sect: %d   ", symbol.n_sect);
			ft_printf("n_desc: %d   ", symbol.n_desc);
			ft_printf("n_type: %d   ", n_type);
		}
		ft_printf("\n");
	}
}

void		print_symbols(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;

	array = (struct nlist_64 *)(ptr + symoff);
	stringtable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		print_symbol(stringtable, array[i]);  //need to sort (ascii) symbols before write them
		i++;
	}
}

void		handle_64(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (struct load_command *)(ptr + sizeof(*header));
	i = 0;
	while (i < ncmds)
	{
		if (DEBUG == 1)
		{
			ft_printf("lc->cmd: %d\n", lc->cmd);
			ft_printf("lc->cmdsize: %d\n", lc->cmdsize);
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
			print_symbols(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
}

void		nm(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (DEBUG == 1)
		ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		if (DEBUG == 1)
			ft_printf("binary for 64 bits\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC)
	{
		if (DEBUG == 1)
			ft_printf("binary for 32 bits\n");
		//handle_32(ptr);
	}
	else
		ft_printf("not a binary for 32 or 64 bits\n");
}
