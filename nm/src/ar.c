#include "nm.h"

void		handle_ar(char *ptr, char *file)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	char			*test;
	int				i;
	int				size;
	int				size_fuck;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size_fuck = catch_size(arch->ar_name);
	ft_printf("size_fuck: %d\n", size_fuck);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck + 4;
	size = *((int *)test);
	ft_printf("size: %d\n", size);
	ft_printf("sizeof(struct ranlib): %d\n", sizeof(struct ranlib));
	size = size / sizeof(struct ranlib);
	ft_printf("size: %d\n", size);
	while (i < size)
	{
		arch = (void*)ptr + ran[i].ran_off;
		size_fuck = catch_size(arch->ar_name);
		ft_printf("\n%s(%s):\n", file, catch_name(arch->ar_name));
		handle_64((void*)arch + sizeof(*arch) + size_fuck);
		i++;
	}
	return ;
}
