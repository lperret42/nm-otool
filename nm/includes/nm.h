#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <ar.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft.h"

# define DEBUG		0

typedef enum		e_error
{
	OPENING_ERROR,
	FSTAT_ERROR,
	MMAP_ERROR,
	MUNMAP_ERROR,
}					t_error;

void	nm(char *ptr, char *name);

int		handle_error(t_error error);
void	handle_64(char *ptr);
void	handle_ar(char *ptr, char *name);

int		catch_size(char *name);
char	*catch_name(char *name);

#endif
