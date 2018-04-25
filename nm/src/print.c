/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:07:10 by lperret           #+#    #+#             */
/*   Updated: 2018/04/25 12:27:43 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		must_be_printed(char letter, t_flags flags)
{
	if (flags.g && !(letter >= 'A' && letter <= 'Z'))
		return (0);
	if (flags.undef == 'u' && (letter != 'u' && letter != 'U'))
		return (0);
	if (flags.undef == 'U' && (letter == 'u' || letter == 'U'))
		return (0);
	return (1);
}

static void		print_sym(t_sym sym, t_flags flags, int bits)
{
	if (!flags.j && flags.undef != 'u')
	{
		if (sym.n_sect != NO_SECT || sym.letter == 'I')
		{
			if (bits == 32)
				ft_printf("%08x", sym.value);
			else
				ft_printf("%016lx", sym.value);
		}
		else
		{
			if (bits == 32)
				ft_printf("%s", "        ");
			else
				ft_printf("%s", "                ");
		}
		ft_printf(" ");
		ft_printf("%c", sym.letter);
		ft_printf(" ");
	}
	ft_printf("%s\n", sym.name);
}

void			print_syms(t_infos infos, int nsyms)
{
	long	i;

	i = -1;
	while (++i < nsyms)
	{
		//if (must_be_printed(syms[i].letter, flags))
		if (must_be_printed(infos.syms[i].letter, infos.flags))
			//if (syms[i].name && !syms[i].for_debug)
			if (infos.syms[i].name && !infos.syms[i].for_debug)
				//print_sym(syms[i], flags, bits);
				print_sym(infos.syms[i], infos.flags, infos.nbits);
	}
}
