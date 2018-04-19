/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:52:37 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 12:38:43 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
/*
static t_sym		get_sym(char debug, unsigned long value,
													int n_sect, char letter)
{
	t_sym		sym;

	sym.for_debug = debug;
	sym.value = (letter == 'u' || letter == 'U') ? -1 : value;
	sym.n_sect = n_sect;
	sym.letter = letter;
	return (sym);
}

static t_sym		*get_syms(struct symtab_command *symtab, char *ptr,
												char **sections_name)
{
	uint32_t			i;
	t_sym				*syms;
	struct nlist_64		*array;
	char				*section_name;
	char				letter;

	if (!(syms = (t_sym*)ft_memalloc(sizeof(t_sym) * symtab->nsyms)))
		return (NULL);
	array = (struct nlist_64 *)(ptr + symtab->symoff);
	i = 0;
	while (i < symtab->nsyms)
	{
		section_name = array[i].n_sect == NO_SECT ? NULL :
						sections_name[array[i].n_sect - 1];
		letter = get_type(array[i].n_type, array[i].n_sect, section_name);
		syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
												array[i].n_sect, letter);
		syms[i].name = ptr + symtab->stroff + array[i].n_un.n_strx;
		i++;
	}
	return (syms);
}

static char			**get_sections_name(struct load_command *lc,
														uint32_t nb_sect)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	uint32_t					i;
	uint32_t					n;
	char						**sections_name;

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
				sec = (void*)sec + sizeof(*sec);
			}
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
	}
	return (sections_name);
}

static uint32_t		get_nb_sects(struct load_command *lc, uint32_t ncmds)
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
*/

static void		print_text_section(uint64_t addr, uint32_t size, char *ptr)
{
	unsigned int	i;

	ft_printf("Contents of (__TEXT,__text) section\n");
	i = 0;
	while (i < size)
	{
		if (i != 0 && i % 16 == 0)
			ft_printf("\n");
		if (i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_printf("%016lx", addr);
			ft_printf("\t");
		}
		ft_printf("%02hhx ", *(ptr + i));
		i++;
	}
	ft_printf("\n");
}


static void		handle_lc_segment_64(struct segment_command_64 *seg, char *ptr)
{
	struct section_64	*sec;
	uint32_t			i;

	i = 0;
	sec = (struct section_64*)((void*)seg + sizeof(struct segment_command_64));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec->sectname, SECT_TEXT) &&
								!ft_strcmp(sec->segname, SEG_TEXT))
			print_text_section(sec->addr, sec->size, ptr + sec->offset);
		sec = (struct section_64*)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

int					handle_64(char *ptr)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64 *)ptr;
	lc = (struct load_command *)(ptr + sizeof(*header));
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			handle_lc_segment_64((struct segment_command_64 *)lc, ptr);
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	return (0);
}
