/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:07:53 by lperret           #+#    #+#             */
/*   Updated: 2018/04/24 13:41:38 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char		get_letter_from_section_name(char *name)
{
	if (DEBUG)
	{
		ft_printf("in get_letter_from_section_name, name: %s\n", name);
		ft_printf("in get_letter_from_section_name, SECT_DATA: %s\n", SECT_DATA);
	}
	if (!ft_strcmp(name, SECT_DATA))
		return ('D');
	else if (!ft_strcmp(name, SECT_BSS))
		return ('B');
	else if (!ft_strcmp(name, SECT_TEXT))
		return ('T');
	else
		return ('S');
}

char			get_type(uint32_t type, int n_value, char *section_name)
{
	char	ret;

	if ((type & N_TYPE) == N_UNDF)
	{
		if (n_value)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = get_letter_from_section_name(section_name);
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0)
		ret += 32;
	return (ret);
}
