/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:07:10 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 18:08:48 by lperret          ###   ########.fr       */
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

static int		print_sym(t_sym sym, t_infos infos)
{
	if (!infos.flags.j && infos.flags.undef != 'u')
	{
		if (sym.n_sect != NO_SECT || sym.letter == 'I' ||
						sym.letter == 'A' || sym.letter == 'C')
		{
			if (infos.nbits == 32)
				ft_printf("%08x", sym.value);
			else
				ft_printf("%016lx", sym.value);
		}
		else
		{
			if (infos.nbits == 32)
				ft_printf("%s", "        ");
			else
				ft_printf("%s", "                ");
		}
		ft_printf(" ");
		ft_printf("%c", sym.letter);
		ft_printf(" ");
	}
	if (check(NULL, sym.name, ft_strlen(sym.name), infos) != 0)
		return (FORMAT_ERROR);
	ft_printf("%s\n", sym.name);
	return (0);
}

int				print_syms(t_infos infos, int nsyms)
{
	long	i;

	i = 0;
	while (i < nsyms)
	{
		if (must_be_printed(infos.syms[i].letter, infos.flags))
			if (infos.syms[i].name && !infos.syms[i].for_debug)
				if (print_sym(infos.syms[i], infos) != 0)
					return (FORMAT_ERROR);
		i++;
	}
	free(infos.syms);
	return (0);
}
