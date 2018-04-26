/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_syms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:24:48 by lperret           #+#    #+#             */
/*   Updated: 2018/04/26 16:46:39 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		swap_sym(t_sym *syms, int a, int b)
{
	t_sym	tmp;

	tmp = syms[a];
	syms[a] = syms[b];
	syms[b] = tmp;
}
