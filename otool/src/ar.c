/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:07:35 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 12:02:55 by lperret          ###   ########.fr       */
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

static int			process_ar(t_ar ar, char *file)
{
	unsigned int		magic_number;

	ft_printf("%s(%s):\n", file, ar.name);
	magic_number = *(unsigned int*)ar.ptr;
	if (magic_number == MH_MAGIC_64)
		return (handle_64(ar.ptr));
	else if (magic_number == MH_MAGIC)
		return (handle_32(ar.ptr));
	else
		return (-1);
	//ft_printf("\n%s(%s):\n", file, ar.name);
	//return (otool(ar.ptr, file));
}

static int			process_ars(t_ar *ars, int nb_ar, char *file)
{
	int		i;
	t_ar	tmp;

	quick_sort_ars(ars, 0, nb_ar - 1);
	i = 0;
	while (i < nb_ar)
	{
		if (!(i > 0 && tmp.name == ars[i].name))
		{
			if (process_ar(ars[i], file) != 0)
				return (-1);
		}
		tmp = ars[i];
		i++;
	}
	return (0);
}

static t_ar			get_ar(char *ptr, struct ranlib ran)
{
	struct ar_hdr	*arch;
	int				size_fuck;
	t_ar			ar;

	arch = (void*)ptr + ran.ran_off;
	size_fuck = get_size(arch->ar_name);
	ar.name = ft_strstr(arch->ar_name, ARFMAG) + ft_strlen(ARFMAG);
	ar.strx = ran.ran_un.ran_strx;
	ar.off = ran.ran_off;
	ar.ptr = (void*)arch + sizeof(*arch) + size_fuck;
	return (ar);
}

int					handle_ar(char *ptr, char *file)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	int				i;
	int				size;
	t_ar			*ars;

	arch = (void*)ptr + SARMAG;
	ran = (void*)ptr + SARMAG + sizeof(*arch) +
							get_size(arch->ar_name) + sizeof(int);
	size = *((int *)((void*)ptr + sizeof(*arch) + SARMAG +
											get_size(arch->ar_name)));
	size = size / sizeof(struct ranlib);
	if (!(ars = (t_ar*)(ft_memalloc(sizeof(t_ar) * size))))
		return (-1);
	i = 0;
	while (i < size)
	{
		ars[i] = get_ar(ptr, ran[i]);
		i++;
	}
	process_ars(ars, size, file);
	free(ars);
	return (0);
}
