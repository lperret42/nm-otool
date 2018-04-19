/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:52:37 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 12:38:43 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void		print_text_section_64(uint64_t addr, uint32_t size, char *ptr)
{
	int				something_writed;
	unsigned int	i;

	something_writed = 0;
	ft_printf("Contents of (__TEXT,__text) section");
	i = 0;
	while (i < size)
	{
		if (i != 0 && i % 16 == 0)
			ft_printf("\n");
		if (i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			if (!something_writed)
				ft_printf("\n");
			ft_printf("%016lx", addr);
			ft_printf("\t");
			something_writed = 1;
		}
		ft_printf("%02hhx ", *(ptr + i));
		i++;
	}
	ft_printf("\n");
}


static void		handle_lc_segment_64(struct segment_command_64 *seg, char *ptr)
{
	struct section_64	*sec;
	uint32_t			i;

	i = 0;
	sec = (struct section_64*)((void*)seg + sizeof(struct segment_command_64));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec->sectname, SECT_TEXT) &&
								!ft_strcmp(sec->segname, SEG_TEXT))
			print_text_section_64(sec->addr, sec->size, ptr + sec->offset);
		sec = (struct section_64*)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

int					handle_64(char *ptr)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64 *)ptr;
	lc = (struct load_command *)(ptr + sizeof(*header));
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			handle_lc_segment_64((struct segment_command_64 *)lc, ptr);
		lc = (struct load_command*)((void*)lc + lc->cmdsize);
		i++;
	}
	return (0);
}
