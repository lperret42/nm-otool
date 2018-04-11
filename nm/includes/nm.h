#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft.h"

# define DEBUG		0

typedef enum		e_error
{
	NO_ARGS_ERROR,
	OPENING_ERROR,
	FSTAT_ERROR,
	MMAP_ERROR,
	MUNMAP_ERROR,
}					t_error;

int		handle_error(t_error error);
void	nm(char *ptr);

#endif
