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

void		process_ar(t_ar ar, char *file, t_options options)
{
	ft_printf("\n%s(%s):\n", file, ar.name);
	nm(ar.ptr, file, options);
}

void		process_ars(t_ar *ars, int nb_ar, char *file, t_options options)
{
	int		i;
	t_ar	tmp;

	quick_sort_ars(ars, 0, nb_ar - 1);
	i = 0;
	while (i < nb_ar)
	{
		if (!(i > 0 && tmp.name == ars[i].name))   //doublon
			process_ar(ars[i], file, options);
		tmp = ars[i];
		i++;
	}
}


void		handle_ar(char *ptr, char *file, t_options options)
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
	process_ars(ars, size, file, options);
	free(ars);
	return ;
}
