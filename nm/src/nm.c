/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:08:16 by lperret           #+#    #+#             */
/*   Updated: 2018/04/24 13:34:24 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		nm(char *ptr, char *file, int nb_real_arg)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (DEBUG)
		ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC || magic_number == MH_MAGIC_64)
	{
		glob()->nbits = (magic_number == MH_MAGIC ? 32 : 64);
		if (DEBUG)
			ft_printf("glob()->nbits: %d\n", glob()->nbits);
		if (nb_real_arg >= 2)
			ft_printf("\n%s:\n", file);
		return (handle_32_64(ptr));
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		return (handle_fat(ptr, file));
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		return (handle_ar(ptr));
	else
	{
		if (DEBUG)
			ft_printf("not object error\n");
		return (NOT_OBJECT_ERROR);
	}
}
