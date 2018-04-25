/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_32_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:37:18 by lperret           #+#    #+#             */
/*   Updated: 2018/04/25 13:20:04 by lperret          ###   ########.fr       */
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

static int			get_syms_32(struct symtab_command *symtab, t_infos *infos)
{
	uint32_t			i;
	struct nlist		*array;
	char				*section_name;

	if (!(infos->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * symtab->nsyms)))
		return (-1);
	if (check_addr(NULL, NULL, (size_t)((void*)infos->ptr + symtab->symoff), *infos) != 0)
		return (-1);
	if (check_addr((void**)&array, infos->ptr + symtab->symoff, sizeof(*array), *infos) != 0)
		return (-1);
	i = 0;
	while (i < symtab->nsyms)
	{
		if (check_addr(NULL, (void*)&array[i], 0, *infos) != 0)
			return (-1);
		section_name = array[i].n_sect == NO_SECT ? NULL :
						infos->sec_names[array[i].n_sect - 1];
		infos->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
	array[i].n_sect, get_type(array[i].n_type, array[i].n_sect, section_name));
		if (check_addr((void**)&infos->syms[i].name, infos->ptr + symtab->stroff + array[i].n_un.n_strx, 0, *infos) != 0)
			return (-1);
		i++;
	}
	free(infos->sec_names);
	return (0);
}

static int			get_syms_64(struct symtab_command *symtab, t_infos *infos)
{
	uint32_t			i;
	struct nlist_64		*array;
	char				*section_name;

	if (!(infos->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * symtab->nsyms)))
		return (-1);
	if (check_addr(NULL, NULL, (size_t)((void*)infos->ptr + symtab->symoff), *infos) != 0)
		return (-1);
	if (check_addr((void**)&array, infos->ptr + symtab->symoff, sizeof(*array), *infos) != 0)
		return (-1);
	i = 0;
	while (i < symtab->nsyms)
	{
		if (DEBUG)
			ft_printf("begin of boucle on symtab->nsyms\n");
		if (check_addr(NULL, (void*)&array[i], 0, *infos) != 0)
			return (-1);
		section_name = array[i].n_sect == NO_SECT ? NULL :
						infos->sec_names[array[i].n_sect - 1];
		infos->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
	array[i].n_sect, get_type(array[i].n_type, array[i].n_sect, section_name));
		if (check_addr((void**)&infos->syms[i].name, infos->ptr + symtab->stroff + array[i].n_un.n_strx, 0, *infos) != 0)
			return (-1);
		if (DEBUG)
			ft_printf("end of boucle on symtab->nsyms\n");
		i++;
	}
	if (DEBUG)
		ft_printf("before free(infos->sec_names)\n");
	free(infos->sec_names);
	return (0);
}

static int			begin_handle_32_64(struct load_command **lc, uint32_t *ncmds, t_infos *infos)
{
	struct mach_header		*head_32;
	struct mach_header_64	*head_64;

	if (infos->nbits == 32)
	{
		if (check_addr((void**)&head_32, infos->ptr, sizeof(*head_32), *infos) != 0)
			return (FORMAT_ERROR);
		if (check_addr((void**)lc, infos->ptr + sizeof(*head_32), sizeof(**lc), *infos) != 0)
			return (FORMAT_ERROR);
		if (get_sec_names(*lc, head_32->ncmds, infos) != 0)
			return (FORMAT_ERROR);
	}
	else
	{
		if (check_addr((void**)&head_64, infos->ptr, sizeof(*head_64), *infos) != 0)
			return (FORMAT_ERROR);
		if (check_addr((void**)lc, infos->ptr + sizeof(*head_64), sizeof(**lc), *infos) != 0)
			return (FORMAT_ERROR);
		if (get_sec_names(*lc, head_64->ncmds, infos) != 0)
			return (FORMAT_ERROR);
	}
	if (!infos->sec_names)
		return (MALLOC_ERROR);
	*ncmds = (infos->nbits == 32 ? head_32-> ncmds : head_64->ncmds);
	return (0);
}


int					handle_32_64(t_infos infos)
{
	uint32_t				i;
	uint32_t				ncmds;
	struct load_command		*lc;
	
	if (begin_handle_32_64(&lc, &ncmds, &infos) != 0)
		return (1);         // return to return the correct error
	i = -1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (check_addr(NULL, lc, sizeof(struct symtab_command), infos) != 0)
				return (FORMAT_ERROR);
			if (infos.nbits == 32)
			{
				if (get_syms_32((struct symtab_command *)lc, &infos) != 0)
					return (FORMAT_ERROR);
			}
			else
			{
				if (get_syms_64((struct symtab_command *)lc, &infos) != 0)
					return (FORMAT_ERROR);
			}
			quick_sort_syms(infos.syms, ((struct symtab_command *)lc)->nsyms, infos.flags);
			print_syms(infos, ((struct symtab_command *)lc)->nsyms);
			free(infos.syms);
			break ;
		}
		if (check_addr((void**)&lc, (void*)lc + lc->cmdsize, sizeof(*lc), infos) != 0)
			return (FORMAT_ERROR);
	}
	return (0);
}
