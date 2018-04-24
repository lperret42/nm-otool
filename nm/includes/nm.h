/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:44:43 by lperret           #+#    #+#             */
/*   Updated: 2018/04/24 13:52:45 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

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

# define DEBUG					1
# define RECOGNIZED_OPTIONS		"gnpruUj"

typedef struct mach_header			header;
typedef struct mach_header_64		header_64;
typedef struct segment_command		seg_com;
typedef struct segment_command_64	seg_com_64;

typedef enum	e_error
{
	NO_ERROR,
	UNRECOGNIZED_OPTION_ERROR,
	NOT_OBJECT_ERROR,
	OPENING_ERROR,
	FSTAT_ERROR,
	MMAP_ERROR,
	MUNMAP_ERROR,
	MALLOC_ERROR,
	FORMAT_ERROR,
}				t_error;

typedef struct	s_flags
{
	char			error;
	char			g;
	char			order;
	char			undef;
	char			j;
}				t_flags;

typedef struct	s_sym
{
	char			for_debug;
	long			value;
	int				n_sect;
	char			letter;
	char			*name;
}				t_sym;

typedef struct	s_ar
{
	char			*name;
	uint64_t		strx;
	uint64_t		off;
	void			*ptr;
}				t_ar;

typedef struct	s_glob
{
	t_flags			flags;
	char			*filename;
	char			*ptr;
	uint64_t		filesize;
	int				nbits;
	char			**sec_names;
	struct segment_command		*seg_32;
	struct segment_command_64	*seg_64;
	struct section				*sec_32;
	struct section_64			*sec_64;
	t_sym			*syms;
}				t_glob;

t_glob			*glob(void);

void			**get_addr_max(void);
int				check_addr(void **dst, void *addr, size_t size);

int				nm(char *ptr, char *name, int nb_real_arg);

char			get_type(uint32_t type, int n_value, char *section_name);

void			quick_sort_ars(t_ar *ars, int begin, int end);
void			swap_sym(t_sym *syms, int a, int b);
void			quick_sort_syms_ascii_reverse(t_sym *syms, int begin, int end);
void			quick_sort_syms(t_sym *syms, int nsyms, t_flags flags);

int				handle_error(t_error error, char *file, int nb_real_arg);

int				handle_ar(char *ptr);
int				handle_fat(char *ptr, char *name);
int				handle_32_64(char *ptr);
int				get_sec_names(struct load_command *lc, uint32_t ncmds);

void			print_syms(int nsyms);

#endif
