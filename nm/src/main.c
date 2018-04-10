#include "nm.h"

void		print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;

	array = (struct nlist_64 *)(ptr + symoff);
	stringtable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
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
		if (lc->cmd == LC_SYMTAB)
		{
			ft_printf("C'est le bon\n");
			sym = (struct symtab_command *)lc;
			ft_printf("nb symboles: %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
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
	ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		ft_printf("magic_number: je suis un binaire pour 64 bits\n");
		handle_64(ptr);
	}
}

int			main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (ac != 2)
	{
		ft_printf("Please give me an argument\n");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_printf("open failure\n");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_printf("fstat failure\n");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("mmap failure\n");
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(0, buf.st_size) < 0)
	{
		ft_printf("mummap failure\n");
		return (EXIT_FAILURE);
	}
	return 0;
}
