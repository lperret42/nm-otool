/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:08:16 by lperret           #+#    #+#             */
/*   Updated: 2018/04/23 20:43:21 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		nm(char *ptr, char *file, t_options options, int nb_real_arg)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (DEBUG)
		ft_printf("magic_number: %#x\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		if (nb_real_arg >= 2)
			//ft_printf("\n");
			ft_printf("\n%s:\n", file);
		return (handle_64(ptr, options));
	}
	else if (magic_number == MH_MAGIC)
	{
		if (nb_real_arg >= 2)
			//ft_printf("\n");
			ft_printf("\n%s:\n", file);
		return (handle_32(ptr, options));
	}
		else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		return (handle_fat(ptr, file, options));
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		return (handle_ar(ptr, file, options));
	else
		return (NOT_OBJECT_ERROR);
}
