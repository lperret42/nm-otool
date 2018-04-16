/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:52:37 by lperret           #+#    #+#             */
/*   Updated: 2018/04/16 17:01:30 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_sym		get_sym(char for_debug, unsigned long value, int n_sect,
												char letter, char *name)
{
	t_sym		sym;

	if (DEBUG)
	{
		ft_printf("n_sect: %d\n", n_sect);
		ft_printf("name: %s\n", name);
	}
	sym.for_debug = for_debug;
	sym.value = (letter == 'u' || letter == 'U') ? -1 : value;
	sym.n_sect = n_sect;
	sym.letter = letter;
	sym.name = name;
	return (sym);
}

t_sym		*get_syms(int nsyms, int symoff, int stroff, char *ptr,
												char **sections_name)
{
	int					i;
	t_sym				*syms;
	struct nlist_64		*array;
	char				*section_name;
	char				letter;

	if (!(syms = (t_sym*)ft_memalloc(sizeof(t_sym) * nsyms)))
		return (NULL);
	array = (struct nlist_64 *)(ptr + symoff);
	i = 0;
	while (i < nsyms)
	{
		section_name = array[i].n_sect == NO_SECT ? NULL :
						sections_name[array[i].n_sect - 1];
		letter = get_type(array[i].n_type, array[i].n_sect, section_name);
		syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
			array[i].n_sect, letter, ptr + stroff + array[i].n_un.n_strx);
		i++;
	}
	return (syms);
}

char		**get_sections_name(struct load_command *lc, uint32_t nb_sect)
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

void		handle_64(char *ptr, t_options opts)
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
			quick_sort_syms(syms, ((struct symtab_command *)lc)->nsyms, opts);
			print_syms(syms, ((struct symtab_command *)lc)->nsyms);
			free(syms);
			break ;
		}
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	free(sections_name);
}
