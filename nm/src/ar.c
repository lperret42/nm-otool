/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:07:35 by lperret           #+#    #+#             */
/*   Updated: 2018/04/24 13:52:28 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			get_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}
/*
//static int			process_ar(t_ar ar, char *file, t_flags flags)
static int			process_ar(t_ar ar, char *file)
{
	ft_printf("\n%s(%s):\n", file, ar.name);
	//return (nm(ar.ptr, file, flags, 0));
	return (nm(ar.ptr, file, 0));
}


static int			process_ars(t_ar *ars, int nb_ar, char *file)
														//t_flags flags)
{
	int		i;
	t_ar	tmp;

	quick_sort_ars(ars, 0, nb_ar - 1);
	i = 0;
	while (i < nb_ar)
	{
		if (!(i > 0 && tmp.name == ars[i].name))
		{
			//if (process_ar(ars[i], file, flags) != 0)
			if (process_ar(ars[i], file) != 0)
				return (-1);
		}
		tmp = ars[i];
		i++;
	}
	return (0);
}

//static t_ar			get_ar(char *ptr, struct ranlib ran)
static t_ar			get_ar(struct ar_hdr *arch)
{
	//struct ar_hdr	*arch;
	struct ranlib	ran;
	int				size;
	t_ar			ar;

	//arch = (void*)ptr + ran.ran_off;
	ran = *((struct ranlib *)arch);
	size = get_size(arch->ar_name);
	ar.name = ft_strstr(arch->ar_name, ARFMAG) + ft_strlen(ARFMAG);
	ar.strx = ran.ran_un.ran_strx;
	ar.off = ran.ran_off;
	ar.ptr = (void*)arch + sizeof(*arch) + size;
	return (ar);
}
*/

void				print_arch(struct ar_hdr *arch)
{
	ft_printf("\n%s(%s):\n", glob()->filename, (void*)arch + sizeof(*arch));
	nm((void*)arch + + sizeof(*arch) + get_size(arch->ar_name), NULL, 0);
}

int					handle_ar(char *ptr)
{
	struct ar_hdr	*arch;

	arch = (void*)ptr + SARMAG;
	arch = (void*)arch + sizeof(*arch) + ft_atoi(arch->ar_size);
	while ((void*)arch < (void*)(glob()->ptr + glob()->filesize))
	{
		print_arch(arch);
		arch = (void*)arch + sizeof(*arch) + ft_atoi(arch->ar_size);
	}
	return (0);
}
