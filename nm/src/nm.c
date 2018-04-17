/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:08:16 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 15:24:21 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		nm(char *ptr, char *file, t_options options)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (DEBUG == 1)
		ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		if (DEBUG == 1)
			ft_printf("binary for 64 bits\n");
		return (handle_64(ptr, options));
	}
	else if (magic_number == MH_MAGIC)
	{
		if (DEBUG == 1)
			ft_printf("binary for 32 bits\n");
		return (handle_32(ptr, options));    //need to write a handle_32 function
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		if (DEBUG == 1)
			ft_printf("FAT binary\n");
		return (handle_fat(ptr, file, options));
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
	{
		if (DEBUG == 1)
			ft_printf("ar binary\n");
		return (handle_ar(ptr, file, options));
	}
	else
	{
		ft_printf("not a binary for 32 or 64 bits\n");
		return (-1);
		//handle_64(ptr, options);
	}
}
