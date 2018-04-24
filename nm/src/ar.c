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

//int					handle_ar(char *ptr, char *file, t_flags flags)
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
	//while (i < size)
	while ((void*)arch < (void*)(glob()->ptr + glob()->filesize))
	{
		//ars[i] = get_ar(ptr, ran[i]);
		ars[i] = get_ar(arch);
		arch = (void*)arch + sizeof(*arch) + ft_atoi(arch->ar_size);
		//i++;
	}
	//process_ars(ars, size, file, flags);
	process_ars(ars, size, file);
	free(ars);
	return (0);
}
