/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:44:43 by lperret           #+#    #+#             */
/*   Updated: 2018/04/26 16:47:59 by lperret          ###   ########.fr       */
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

# define RECOGNIZED_OPTIONS		"gnpruUj"

typedef struct mach_header			header;
typedef struct mach_header_64		header_64;
typedef struct fat_arch				fat_ar;
typedef struct fat_arch_64			fat_ar_64;
typedef struct symtab_command		sym_com;
typedef struct segment_command		seg_com;
typedef struct segment_command_64	seg_com_64;

typedef enum	e_error
{
	NO_ERROR,
	UNRECOGNIZED_OPTION_ERROR,
	NOT_OBJECT_ERROR,
	OPENING_ERROR,
	FSTAT_ERROR,
	EMPTY_FILE_ERROR,
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

typedef struct	s_infos
{
	t_flags					flags;
	int						nbfiles;
	char					*filename;
	char					*ptr;
	uint64_t				filesize;
	int						nbits;
	int						swap;
	struct load_command		*lc;
	uint32_t				ncmds;
	char					**sec_names;
	uint32_t				symoff;
	uint32_t				stroff;
	int						host_cpu;
	uint32_t				nsyms;
	t_sym					*syms;
}				t_infos;

int				nm(t_infos infos);

int				check_addr(void **dst, void *addr, size_t size, t_infos infos);
int				check_sym_name(char *name, t_infos infos);

int				handle_ars(t_infos infos);
int				handle_fats(t_infos infos);
int				handle_32_64(t_infos infos);

uint32_t		swap32(uint32_t nb, int to_swap);
uint64_t		swap64(uint64_t nb, int to_swap);

char			get_type(uint32_t type, int n_value, char *section_name);

void			swap_sym(t_sym *syms, int a, int b);
void			quick_sort_syms_ascii_reverse(t_sym *syms, int begin, int end);
void			quick_sort_syms(t_sym *syms, int nsyms, t_flags flags);

int				handle_error(t_error error, t_infos infos);

int				get_sec_names(struct load_command *lc, uint32_t ncmds,
															t_infos *infos);

int				print_syms(t_infos infos, int nsyms);

t_sym			get_sym(char debug, unsigned long value, int n_sect,
															char letter);

#endif
