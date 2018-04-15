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

typedef enum	e_error
{
	OPENING_ERROR,
	FSTAT_ERROR,
	MMAP_ERROR,
	MUNMAP_ERROR,
}					t_error;

typedef struct	s_sym
{
	unsigned long	value;
	int				n_sect;
	char			letter;
	char			*name;
}				t_sym;

typedef struct	s_ar
{
	char		*name;
	uint64_t	strx;
	uint64_t	off;
	void		*ptr;
}				t_ar;

void			nm(char *ptr, char *name);

void			quick_sort_ars(t_ar *ars, int begin, int end);
void			quick_sort_syms_ascii(t_sym *syms, int begin, int end);
void			quick_sort_syms_numerically(t_sym *syms, int begin, int end);
void			quick_sort_syms_same_ascii_numerically(t_sym *syms, int nsyms);

int				handle_error(t_error error);

void			handle_64(char *ptr);
void			handle_ar(char *ptr, char *name);

int				catch_size(char *name);
char			*catch_name(char *name);

#endif
