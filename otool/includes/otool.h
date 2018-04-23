#ifndef OTOOL_H
# define OTOOL_H

# include <sys/mman.h>
# include <ar.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft.h"

typedef enum	e_error
{
	NO_ERROR,
	NO_ARG_ERROR,
	NOT_OBJECT_ERROR,
	OPENING_ERROR,
	FSTAT_ERROR,
	MMAP_ERROR,
	MUNMAP_ERROR,
	MALLOC_ERROR,
}				t_error;

typedef struct	s_ar
{
	char			*name;
	uint64_t		strx;
	uint64_t		off;
	void			*ptr;
}				t_ar;

int				otool(char *ptr, char *name);

int				handle_error(t_error error, char *file);

int				handle_ar(char *ptr, char *name);
int				handle_fat(char *ptr, char *name);
int				handle_32(char *ptr);
int				handle_64(char *ptr);

void			quick_sort_ars(t_ar *ars, int begin, int end);

#endif
