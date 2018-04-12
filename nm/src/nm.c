#include "nm.h"

void		nm(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (DEBUG == 1)
		ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		if (DEBUG == 1)
			ft_printf("binary for 64 bits\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC)
	{
		if (DEBUG == 1)
			ft_printf("binary for 32 bits\n");
		//handle_32(ptr);
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
	{
		if (DEBUG == 1)
			ft_printf("ar binary\n");
		handle_ar(ptr);
	}
	else
	{
		ft_printf("not a binary for 32 or 64 bits\n");
		handle_64(ptr);
	}
}
