#include "nm.h"

int		handle_error(t_error error)
{
	if (error == NO_ARGS_ERROR)
		ft_printf("Please give me an argument\n");
	else if (error == OPENING_ERROR)
		//ft_printf("Can't open file.\n");
		ft_putendl("Can't open file.");
	else if (error == FSTAT_ERROR)
		ft_printf("fstat failure\n");
	else if (error == MMAP_ERROR)
		ft_printf("mmap failure\n");
	else if (error == MUNMAP_ERROR)
		ft_printf("mummap failure\n");
	return (EXIT_FAILURE);
}
