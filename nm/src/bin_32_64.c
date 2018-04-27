/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_32_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:37:18 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 18:14:51 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			get_syms_32(t_infos *infos)
{
	uint32_t			i;
	struct nlist		*array;
	char				*section_name;

	if (!(infos->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * infos->nsyms)))
		return (MALLOC_ERROR);
	if (check(NULL, infos->ptr, infos->symoff +
				infos->nsyms * sizeof(*array), *infos) != 0)
		return (FORMAT_ERROR);
	array = (struct nlist*)((void*)infos->ptr + infos->symoff);
	i = 0;
	while (i < infos->nsyms)
	{
		section_name = array[i].n_sect == NO_SECT ? NULL :
						infos->sec_names[array[i].n_sect - 1];
		infos->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0,
			swap32(array[i].n_value, infos->swap), array[i].n_sect,
			get_type(array[i].n_type, array[i].n_value, section_name));
		infos->syms[i].name = infos->ptr + infos->stroff +
								swap32(array[i].n_un.n_strx, infos->swap);
		i++;
	}
	free(infos->sec_names);
	return (0);
}

static int			get_syms_64(t_infos *infos)
{
	uint32_t			i;
	struct nlist_64		*array;
	char				*section_name;

	if (!(infos->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * infos->nsyms)))
		return (MALLOC_ERROR);
	if (check(NULL, infos->ptr, infos->symoff +
				infos->nsyms * sizeof(*array), *infos) != 0)
		return (FORMAT_ERROR);
	array = (struct nlist_64 *)((void*)infos->ptr + infos->symoff);
	i = 0;
	while (i < infos->nsyms)
	{
		section_name = array[i].n_sect == NO_SECT ? NULL :
						infos->sec_names[array[i].n_sect - 1];
		infos->syms[i] = get_sym(array[i].n_type & N_STAB ? 1 : 0,
			swap64(array[i].n_value, infos->swap), array[i].n_sect,
			get_type(array[i].n_type, array[i].n_value, section_name));
		infos->syms[i].name = infos->ptr + infos->stroff +
								swap32(array[i].n_un.n_strx, infos->swap);
		i++;
	}
	free(infos->sec_names);
	return (0);
}

static int			handle_syms(t_infos *infos)
{
	uint64_t	i;
	int			error;

	if (check(NULL, infos->lc, sizeof(t_sym_com), *infos) != 0)
		return (FORMAT_ERROR);
	infos->symoff = swap32(((t_sym_com *)infos->lc)->symoff, infos->swap);
	infos->nsyms = swap32(((t_sym_com *)infos->lc)->nsyms, infos->swap);
	infos->stroff = swap32(((t_sym_com *)infos->lc)->stroff, infos->swap);
	infos->strsize = swap32(((t_sym_com *)infos->lc)->strsize, infos->swap);
	if (check(NULL, (void*)infos->ptr + infos->stroff, infos->strsize,
																*infos) != 0)
		return (FORMAT_ERROR);
	if ((error = (infos->nbits == 32 ? get_syms_32(infos) :
										get_syms_64(infos))) != NO_ERROR)
		return (error);
	i = 0;
	while (i < infos->nsyms)
		if (check_sym_name(infos->syms[i++].name, *infos) != 0)
			return (FORMAT_ERROR);
	quick_sort_syms(infos->syms, infos->nsyms, infos->flags);
	if (print_syms(*infos, infos->nsyms) != 0)
		return (FORMAT_ERROR);
	return (0);
}

static int			get_data(t_infos *infos)
{
	uint32_t	header_size;

	header_size = (infos->nbits == 32 ? sizeof(t_header) : sizeof(t_header_64));
	if (check(NULL, infos->ptr, header_size, *infos) != 0)
		return (FORMAT_ERROR);
	infos->ncmds = (infos->nbits == 32 ?
			swap32(((t_header*)(infos->ptr))->ncmds, infos->swap) :
			swap32(((t_header_64*)(infos->ptr))->ncmds, infos->swap));
	infos->lc = (void*)infos->ptr + header_size;
	if (get_sec_names(infos->lc, infos->ncmds, infos) != 0)
		return (FORMAT_ERROR);
	if (!infos->sec_names)
		return (MALLOC_ERROR);
	return (0);
}

int					handle_32_64(t_infos infos)
{
	int						error;
	uint32_t				i;
	uint32_t				cmd;

	error = get_data(&infos);
	if (error != NO_ERROR)
		return (error);
	i = 0;
	while (i < infos.ncmds)
	{
		if (check(NULL, infos.lc, sizeof(struct load_command), infos) != 0)
			return (FORMAT_ERROR);
		cmd = swap32(infos.lc->cmd, infos.swap);
		if (cmd == LC_SYMTAB)
			return (handle_syms(&infos));
		infos.lc = (void*)infos.lc + swap32(infos.lc->cmdsize, infos.swap);
		i++;
	}
	return (0);
}
