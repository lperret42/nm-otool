/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:37:58 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 17:32:48 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_text_sec_32(uint32_t addr, uint32_t size, char *ptr,
															t_infos infos)
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
			ft_printf("%08lx\t", addr);
			something_writed = 1;
		}
		ft_printf("%02hhx", *(ptr + i));
		i++;
		if (!infos.swap || i % 4 == 0)
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	print_text_sec_64(uint64_t addr, uint64_t size, char *ptr,
															t_infos infos)
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
			ft_printf("%016lx\t", addr);
			something_writed = 1;
		}
		ft_printf("%02hhx", *(ptr + i));
		i++;
		if (!infos.swap || i % 4 == 0)
			ft_printf(" ");
	}
	ft_printf("\n");
}
