/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:07:35 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 10:16:13 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			catch_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}

char		*catch_name(char *name)
{
	int		length;

	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
}

int			process_ar(t_ar ar, char *file, t_options options)
{
	ft_printf("\n%s(%s):\n", file, ar.name);
	return (nm(ar.ptr, file, options));
}

int			process_ars(t_ar *ars, int nb_ar, char *file, t_options options)
{
	int		i;
	t_ar	tmp;

	quick_sort_ars(ars, 0, nb_ar - 1);
	i = 0;
	while (i < nb_ar)
	{
		if (!(i > 0 && tmp.name == ars[i].name))
			return (process_ar(ars[i], file, options));
		tmp = ars[i];
		i++;
	}
	return (0);
}

int			handle_ar(char *ptr, char *file, t_options options)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	char			*test;
	int				i;
	int				size;
	int				size_fuck;

	t_ar			*ars;

	arch = (void*)ptr + SARMAG;
	size_fuck = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck;
	ran = (void*)test + sizeof(int);
	size = *((int *)test);
	size = size / sizeof(struct ranlib);
	if (!(ars = (t_ar*)(ft_memalloc(sizeof(t_ar) * size))))
		return (-1);
	i = 0;
	while (i < size)
	{
		arch = (void*)ptr + ran[i].ran_off;
		size_fuck = catch_size(arch->ar_name);
		ars[i].name = catch_name(arch->ar_name);
		ars[i].strx = ran[i].ran_un.ran_strx;
		ars[i].off = ran[i].ran_off;
		ars[i].ptr = (void*)arch + sizeof(*arch) + size_fuck;
		i++;
	}
	process_ars(ars, size, file, options);
	free(ars);
	return (0);
}
