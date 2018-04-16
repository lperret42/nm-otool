#include "nm.h"

void		nm(char *ptr, char *file, t_options options)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (DEBUG == 1)
		ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		if (DEBUG == 1)
			ft_printf("binary for 64 bits\n");
		handle_64(ptr, options);
	}
	else if (magic_number == MH_MAGIC)
	{
		if (DEBUG == 1)
			ft_printf("binary for 32 bits\n");
		handle_64(ptr, options);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		if (DEBUG == 1)
			ft_printf("FAT binary\n");
		handle_fat(ptr, file, options);
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
	{
		if (DEBUG == 1)
			ft_printf("ar binary\n");
		handle_ar(ptr, file, options);
	}
	else
	{
		ft_printf("not a binary for 32 or 64 bits\n");
		handle_64(ptr, options);
	}
}
