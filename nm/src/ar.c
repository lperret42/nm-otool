#include "nm.h"

void		process_ar(t_ar ar, char *file)
{
	ft_printf("\n%s(%s):\n", file, ar.name);
	nm(ar.ptr, file);
}

void		sort_ars_by_strx(t_ar *ars, int nb_ar)
{
	int			i;
	t_ar		tmp;

	i = 0;
	while (i < nb_ar - 1)
	{
		if (ars[i + 1].strx < ars[i].strx)
		{
			tmp = ars[i];
			ars[i] = ars[i + 1];
			ars[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void		process_ars(t_ar *ars, int nb_ar, char *file)
{
	int		i;
	t_ar	tmp;

	//sort_ars_by_strx(ars, nb_ar);
	quick_sort(ars, 0, nb_ar - 1);
	i = 0;
	while (i < nb_ar)
	{
		if (!(i > 0 && tmp.name == ars[i].name))   //doublon
			process_ar(ars[i], file);
		tmp = ars[i];
		i++;
	}
}


void		handle_ar(char *ptr, char *file)
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
	if (DEBUG)
	{
		ft_printf("size_fuck: %d\n", size_fuck);
		ft_printf("size: %d\n", size);
		ft_printf("sizeof(*arch): %d\n", sizeof(*arch));
		ft_printf("sizeof(struct ranlib): %d\n", sizeof(struct ranlib));
		ft_printf("size: %d\n", size);
		ft_printf("extended: %d\n", ft_atoi(arch->ar_name +
												ft_strlen(AR_EFMT1)));
	}
	if (!(ars = (t_ar*)(ft_memalloc(sizeof(t_ar) * size))))
		return ;    // error to handle
	i = 0;
	while (i < size)
	{
		arch = (void*)ptr + ran[i].ran_off;
		size_fuck = catch_size(arch->ar_name);
		ars[i].name = catch_name(arch->ar_name);
		ars[i].strx = ran[i].ran_un.ran_strx;
		ars[i].off = ran[i].ran_off;
		ars[i].ptr = (void*)arch + sizeof(*arch) + size_fuck;
		if (DEBUG)
		{
			ft_printf("\n%s(%s):\n", file, catch_name(arch->ar_name));
			ft_printf("ran[i].ran_off:  %u\n", ran[i].ran_off);
			ft_printf("ran[i].ran_un.ran_strx:  %u\n",
												ran[i].ran_un.ran_strx);
		}
		i++;
	}
	process_ars(ars, size, file);
	free(ars);
	return ;
}
