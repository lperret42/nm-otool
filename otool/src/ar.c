/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:07:35 by lperret           #+#    #+#             */
/*   Updated: 2018/04/30 10:22:50 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int			get_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}

static int			handle_ar(struct ar_hdr *arch, t_infos infos)
{
	t_infos		new_infos;

	if (check(NULL, (void*)arch, sizeof(*arch), infos) != 0)
		return (FORMAT_ERROR);
	if (check(NULL, (void*)arch + sizeof(*arch),
									ft_atoi(arch->ar_size), infos) != 0)
		return (FORMAT_ERROR);
	ft_memcpy(&new_infos, &infos, sizeof(t_infos));
	new_infos.nbfiles = 0;
	new_infos.filename = (void*)arch + sizeof(*arch);
	new_infos.ptr = (void*)arch + sizeof(*arch) + get_size(arch->ar_name);
	new_infos.filesize = sizeof(*arch) + ft_atoi(arch->ar_size);
	if (!(new_infos.filesize < infos.filesize))
		return (FORMAT_ERROR);
	ft_printf("%s(%s):\n", infos.filename, (void*)arch + sizeof(*arch));
	return (otool(new_infos));
}

int					handle_ars(t_infos infos)
{
	int				error;
	struct ar_hdr	*arch;

	ft_printf("Archive : %s\n", infos.filename);
	arch = (void*)infos.ptr + SARMAG;
	if (check(NULL, (void*)arch, sizeof(*arch), infos) != 0)
		return (FORMAT_ERROR);
	arch = (void*)arch + sizeof(*arch) + ft_atoi(arch->ar_size);
	while ((void*)arch < (void*)(infos.ptr + infos.filesize))
	{
		error = handle_ar(arch, infos);
		if (error != NO_ERROR)
			return (error);
		arch = (void*)arch + sizeof(*arch) + ft_atoi(arch->ar_size);
	}
	return (0);
}
