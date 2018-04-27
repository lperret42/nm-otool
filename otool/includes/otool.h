/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:44:43 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 17:49:08 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct mach_header			t_header;
typedef struct mach_header_64		t_header_64;
typedef struct fat_arch				t_fat_ar;
typedef struct fat_arch_64			t_fat_ar_64;
typedef struct symtab_command		t_sym_com;
typedef struct segment_command		t_seg_com;
typedef struct segment_command_64	t_seg_com_64;
typedef struct section				t_sec;
typedef struct section_64			t_sec_64;

typedef enum	e_error
{
	NO_ERROR,
	NO_ARG_ERROR,
	UNRECOGNIZED_OPTION_ERROR,
	NOT_OBJECT_ERROR,
	OPENING_ERROR,
	FSTAT_ERROR,
	MMAP_ERROR,
	MUNMAP_ERROR,
	MALLOC_ERROR,
	FORMAT_ERROR,
}				t_error;

typedef struct	s_infos
{
	int						nbfiles;
	char					*filename;
	char					*ptr;
	uint64_t				filesize;
	int						nbits;
	int						swap;
	struct load_command		*lc;
	uint32_t				ncmds;
	uint32_t				nsects;
	int						host_cpu;
}				t_infos;

int				otool(t_infos infos);

int				check(void **dst, void *addr, size_t size, t_infos infos);

int				handle_fats(t_infos infos);
int				handle_ars(t_infos infos);
int				handle_32_64(t_infos infos);

uint32_t		swap32(uint32_t nb, int to_swap);
uint64_t		swap64(uint64_t nb, int to_swap);

int				handle_error(t_error error, t_infos infos);

void			print_text_sec_32(uint32_t addr, uint32_t size, char *ptr,
															t_infos infos);
void			print_text_sec_64(uint64_t addr, uint64_t size, char *ptr,
															t_infos infos);

#endif
