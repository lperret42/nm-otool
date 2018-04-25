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
		return (MALLOC_ERROR);
	if (check_addr(NULL, infos->ptr, symtab->symoff + symtab->nsyms * sizeof(*array), *infos) != 0)
		return (FORMAT_ERROR);
	array = (struct nlist*)((void*)infos->ptr + symtab->symoff);
	i = 0;
	while (i < symtab->nsyms)
	{
		section_name = array[i].n_sect == NO_SECT ? NULL :
						infos->sec_names[array[i].n_sect - 1];
		infos->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
	array[i].n_sect, get_type(array[i].n_type, array[i].n_sect, section_name));
		infos->syms[i].name = infos->ptr + symtab->stroff + array[i].n_un.n_strx;
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
		return (MALLOC_ERROR);
	if (check_addr(NULL, infos->ptr, symtab->symoff + symtab->nsyms * sizeof(*array), *infos) != 0)
		return (FORMAT_ERROR);
	array = (struct nlist_64*)((void*)infos->ptr + symtab->symoff);
	i = 0;
	while (i < symtab->nsyms)
	{
		section_name = array[i].n_sect == NO_SECT ? NULL :
						infos->sec_names[array[i].n_sect - 1];
		infos->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0, array[i].n_value,
	array[i].n_sect, get_type(array[i].n_type, array[i].n_sect, section_name));
		infos->syms[i].name = infos->ptr + symtab->stroff + array[i].n_un.n_strx;
		i++;
	}
	free(infos->sec_names);
	return (0);
}

static int				get_data(t_infos *infos)
{
	uint32_t	header_size;

	header_size = (infos->nbits == 32 ? sizeof(header) : sizeof(header_64));
	if (check_addr(NULL, infos->ptr, header_size, *infos) != 0)
		return (FORMAT_ERROR);
	infos->ncmds = (infos->nbits == 32 ? ((header*)(infos->ptr))->ncmds :
							((header_64*)(infos->ptr))->ncmds);
	infos->lc = (void*)infos->ptr + header_size;
	if (get_sec_names(infos->lc, infos->ncmds, infos) != 0)
		return (FORMAT_ERROR);
	if (!infos->sec_names)
		return (MALLOC_ERROR);
	return (0);
}

static int			handle_syms(t_infos *infos)
{
	int		error;

	if (check_addr(NULL, infos->lc, sizeof(struct symtab_command), *infos) != 0)
		return (FORMAT_ERROR);
	if (infos->nbits == 32)
		error = get_syms_32((struct symtab_command *)infos->lc, infos);
	else
		error = get_syms_64((struct symtab_command *)infos->lc, infos);
	if (error != NO_ERROR)
		return (error);
	quick_sort_syms(infos->syms, ((struct symtab_command *)infos->lc)->nsyms,
											infos->flags);
	if (print_syms(*infos, ((struct symtab_command *)infos->lc)->nsyms) != 0)
		return (FORMAT_ERROR);
	return (0);
}

int					handle_32_64(t_infos infos)
{
	int						error;
	uint32_t				i;
	
	error = get_data(&infos);
	if (error != NO_ERROR)
		return (error);
	i = -1;
	while (++i < infos.ncmds)
	{
		if (check_addr(NULL, infos.lc, sizeof(struct load_command), infos) != 0)
			return (FORMAT_ERROR);
		if (infos.lc->cmd == LC_SYMTAB)
			return (handle_syms(&infos));
		infos.lc = (void*)infos.lc + infos.lc->cmdsize;
	}
	return (0);
}
