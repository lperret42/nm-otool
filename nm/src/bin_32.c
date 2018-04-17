/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:01:46 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 12:38:58 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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
	struct nlist		*array;
	char				*section_name;
	char				letter;

	if (!(syms = (t_sym*)ft_memalloc(sizeof(t_sym) * symtab->nsyms)))
		return (NULL);
	array = (struct nlist *)(ptr + symtab->symoff);
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
	struct segment_command		*seg;
	struct section				*sec;
	uint32_t					i;
	uint32_t					n;
	char						**sections_name;

	if (!(sections_name = (char**)ft_memalloc(sizeof(char*) * (nb_sect + 1))))
		return (NULL);
	i = 0;
	while (i < nb_sect)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sec = (struct section *)((void*)seg + sizeof(*seg));
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
	struct segment_command		*seg;
	uint32_t					i;
	uint32_t					nb_sections;

	nb_sections = 0;
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			nb_sections += seg->nsects;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	return (nb_sections);
}

int					handle_32(char *ptr, t_options opts)
{
	uint32_t				i;
	struct mach_header		*header;
	struct load_command		*lc;
	char					**sect_names;
	t_sym					*syms;

	header = (struct mach_header *)ptr;
	lc = (struct load_command *)(ptr + sizeof(*header));
	if (!(sect_names = get_sections_name(lc, get_nb_sects(lc, header->ncmds))))
		return (-1);
	i = -1;
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			syms = get_syms((struct symtab_command *)lc, ptr, sect_names);
			quick_sort_syms(syms, ((struct symtab_command *)lc)->nsyms, opts);
			print_syms(syms, ((struct symtab_command *)lc)->nsyms, opts, 32);
			free(syms);
			break ;
		}
		lc = (struct load_command *)((void*)lc + lc->cmdsize);
	}
	free(sect_names);
	return (0);
}
