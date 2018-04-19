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

#include "otool.h"

int		otool(char *ptr, char *file)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		ft_printf("%s:\n", file);
		return (handle_64(ptr));
	}
	else if (magic_number == MH_MAGIC)
	{
		ft_printf("%s:\n", file);
		return (handle_32(ptr));
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		return (handle_fat(ptr, file));
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
	{
		ft_printf("Archive : %s\n", file);
		return (handle_ar(ptr, file));
	}
	else
		return (NOT_OBJECT_ERROR);
}
