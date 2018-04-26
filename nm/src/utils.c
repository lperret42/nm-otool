/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 11:17:59 by lperret           #+#    #+#             */
/*   Updated: 2018/04/26 16:46:51 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_sym		get_sym(char debug, unsigned long value,
													int n_sect, char letter)
{
	t_sym		sym;

	sym.for_debug = debug;
	sym.value = (letter == 'u' || letter == 'U') ? -1 : value;
	sym.n_sect = n_sect;
	sym.letter = letter;
	return (sym);
}
