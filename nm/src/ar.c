#include "nm.h"

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
}						t_offlist;


t_offlist		*add_off(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*tmp;
	t_offlist	*tmp2;

	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	if (!lst)
		return (tmp);
	tmp2 = lst;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	return (lst);
}

int			catch_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}

void	go_archive(char *ptr)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	int				i;
	int				size;
	int				size_fuck;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size_fuck = catch_size(arch->ar_name);
	ft_printf("size_fuck: %d\n", size_fuck);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck + 4;
	size = *((int *)test);
	ft_printf("size: %d\n", size);
	ft_printf("sizeof(struct ranlib): %d\n", sizeof(struct ranlib));
	lst = NULL;
	size = size / sizeof(struct ranlib);
	ft_printf("size: %d\n", size);
	while (i < size)
	{
		//lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		ft_printf("ran[i].ran_off: %d\n", ran[i].ran_off);
		ft_printf("ran[i].ran_un.ran_strx: %d\n", ran[i].ran_un.ran_strx);
		i++;
	}
}

void		handle_ar(char *ptr)
{
	/*int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;*/

	go_archive(ptr);
	return ;
	struct ar_hdr		*hdr;

	hdr = (void*)ptr + SARMAG;
	ft_printf("ar_name: %s\n", hdr->ar_name);
	ft_printf("ar_date: %s\n", hdr->ar_date);
	ft_printf("ar_uid: %s\n", hdr->ar_uid);
	ft_printf("ar_gid: %s\n", hdr->ar_gid);
	ft_printf("ar_mode: %s\n", hdr->ar_mode);
	ft_printf("ar_size: %s\n", hdr->ar_size);
	ft_printf("ar_fmag: %s\n", hdr->ar_fmag);

	return ;
	/*header = (struct mach_header_64 *)ptr;
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
			print_symbols(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	*/
}
