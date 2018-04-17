/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:07:10 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 10:31:00 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			must_be_printed(char letter, t_options options)
{
	if (options.g && !(letter >= 'A' && letter <= 'Z'))
		return (0);
	if (options.undef == 'u' && (letter != 'u' || letter != 'U'))
		return (0);
	if (options.undef == 'U' && (letter == 'u' || letter == 'U'))
		return (0);
	return (1);
}

void		print_syms(t_sym *syms, int nsyms, t_options options)
{
	long	i;

	i = -1;
	while (++i < nsyms)
	{
		if (must_be_printed(syms[i].letter, options))
		{
			if (syms[i].name && !syms[i].for_debug)
			{
				if (!options.j && options.undef != 'u')
				{
					if (syms[i].n_sect != NO_SECT)
						ft_printf("%016lx", syms[i].value);
					else
						ft_printf("%s", "                ");
					ft_printf(" ");
					ft_printf("%c", syms[i].letter);
					ft_printf(" ");
				}
				ft_printf("%s\n", syms[i].name);
			}
		}
	}
}
