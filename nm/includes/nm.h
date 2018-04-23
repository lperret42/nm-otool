/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:44:43 by lperret           #+#    #+#             */
/*   Updated: 2018/04/23 21:34:20 by lperret          ###   ########.fr       */
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

typedef struct	s_options
{
	char			error;
	char			g;
	char			order;
	char			undef;
	char			j;
}				t_options;

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

void			**get_addr_max(void);
int				check_addr(void **dst, void *addr, size_t size);

int				nm(char *ptr, char *name, t_options options, int nb_real_arg);

char			get_type(uint32_t type, int n_value, char *section_name);

void			quick_sort_ars(t_ar *ars, int begin, int end);
void			swap_sym(t_sym *syms, int a, int b);
void			quick_sort_syms_ascii_reverse(t_sym *syms, int begin, int end);
void			quick_sort_syms(t_sym *syms, int nsyms, t_options options);

int				handle_error(t_error error, char *file, int nb_real_arg);

int				handle_ar(char *ptr, char *name, t_options options);
int				handle_fat(char *ptr, char *name, t_options options);
int				handle_32(char *ptr, t_options options);
char			**get_section_names_64(struct load_command *lc);
int				handle_64(char *ptr, t_options options);

void			print_syms(t_sym *syms, int nsyms, t_options options, int bits);

#endif
