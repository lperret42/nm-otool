#include "nm.h"

int		handle_error(t_error error)
{
	if (error == UNRECOGNIZED_OPTION_ERROR)
		ft_putendl("Unrecognized option.");
	else if (error == OPENING_ERROR)
		ft_putendl("Can't open file.");
	else if (error == FSTAT_ERROR)
		ft_putendl("fstat failure");
	else if (error == MMAP_ERROR)
		ft_putendl("mmap failure");
	else if (error == MUNMAP_ERROR)
		ft_putendl("mummap failure");
	return (EXIT_FAILURE);
}
