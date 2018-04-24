/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_32_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:37:18 by lperret           #+#    #+#             */
/*   Updated: 2018/04/24 13:37:19 by lperret          ###   ########.fr       */
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

static int			get_syms_32(struct symtab_command *symtab, char *ptr)
{
	uint32_t			i;
	struct nlist		*array;
	char				*section_name;

	if (!(glob()->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * symtab->nsyms)))
		return (-1);
	if (check_addr(NULL, NULL, (size_t)((void*)ptr + symtab->symoff)) != 0)
		return (-1);
	if (check_addr((void**)&array, ptr + symtab->symoff, sizeof(*array)) != 0)
		return (-1);
	i = 0;
	while (i < symtab->nsyms)
	{
		if (DEBUG)
			ft_printf("yo\n");
		if (check_addr(NULL, (void*)&array[i], 0) != 0)
			return (-1);
		section_name = array[i].n_sect == NO_SECT ? NULL :
						glob()->sec_names[array[i].n_sect - 1];
		glob()->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
	array[i].n_sect, get_type(array[i].n_type, array[i].n_sect, section_name));
		if (check_addr((void**)&glob()->syms[i].name, ptr + symtab->stroff + array[i].n_un.n_strx, 0 ) != 0)
			return (-1);
		i++;
	}
	free(glob()->sec_names);
	return (0);
}

static int			get_syms_64(struct symtab_command *symtab, char *ptr)
{
	uint32_t			i;
	struct nlist_64		*array;
	char				*section_name;

	if (!(glob()->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * symtab->nsyms)))
		return (-1);
	if (check_addr(NULL, NULL, (size_t)((void*)ptr + symtab->symoff)) != 0)
		return (-1);
	if (check_addr((void**)&array, ptr + symtab->symoff, sizeof(*array)) != 0)
		return (-1);
	i = 0;
	while (i < symtab->nsyms)
	{
		if (DEBUG)
			ft_printf("yo\n");
		if (check_addr(NULL, (void*)&array[i], 0) != 0)
			return (-1);
		section_name = array[i].n_sect == NO_SECT ? NULL :
						glob()->sec_names[array[i].n_sect - 1];
		glob()->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
	array[i].n_sect, get_type(array[i].n_type, array[i].n_sect, section_name));
		if (check_addr((void**)&glob()->syms[i].name, ptr + symtab->stroff + array[i].n_un.n_strx, 0 ) != 0)
			return (-1);
		i++;
	}
	free(glob()->sec_names);
	return (0);
}

int					handle_32_64(char *p)
{
	uint32_t				i;
	struct mach_header		*head_32;
	struct mach_header_64	*head_64;
	struct load_command		*lc;

	if (glob()->nbits == 32)
	{
		if (check_addr((void**)&head_32, p, sizeof(*head_32)) != 0)
			return (FORMAT_ERROR);
		if (check_addr((void**)&lc, p + sizeof(*head_32), sizeof(*lc)) != 0)
			return (FORMAT_ERROR);
		if (get_sec_names(lc, head_32->ncmds) != 0)
			return (FORMAT_ERROR);
	}
	else
	{
		if (check_addr((void**)&head_64, p, sizeof(*head_64)) != 0)
			return (FORMAT_ERROR);
		if (check_addr((void**)&lc, p + sizeof(*head_64), sizeof(*lc)) != 0)
			return (FORMAT_ERROR);
		if (get_sec_names(lc, head_64->ncmds) != 0)
			return (FORMAT_ERROR);
	}
	if (!glob()->sec_names)
		return (MALLOC_ERROR);
	i = -1;
	while (++i < (glob()->nbits == 32 ? head_32->ncmds : head_64->ncmds))
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (check_addr(NULL, lc, sizeof(struct symtab_command)) != 0)
				return (FORMAT_ERROR);
			if (glob()->nbits == 32)
			{
				if (get_syms_32((struct symtab_command *)lc, p) != 0)
					return (FORMAT_ERROR);
			}
			else
			{
				if (get_syms_64((struct symtab_command *)lc, p) != 0)
					return (FORMAT_ERROR);
			}
			quick_sort_syms(glob()->syms, ((struct symtab_command *)lc)->nsyms, glob()->flags);
			print_syms(((struct symtab_command *)lc)->nsyms);
			free(glob()->syms);
			break ;
		}
		if (check_addr((void**)&lc, (void*)lc + lc->cmdsize, sizeof(*lc)) != 0)
			return (FORMAT_ERROR);
	}
	return (0);
}
