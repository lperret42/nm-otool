/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_syms_ascii_reverse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:41:22 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 11:41:36 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	quick_sort_syms_ascii_reverse(t_sym *syms, int begin, int end)
{
	int			left;
	int			right;
	char		*pivot;

	left = begin - 1;
	right = end + 1;
	pivot = syms[begin].name;
	if (begin >= end)
		return ;
	while (1)
	{
		while (ft_strcmp(syms[++left].name, pivot) > 0)
			;
		while (ft_strcmp(syms[--right].name, pivot) < 0)
			;
		if (left < right)
			swap_sym(syms, left, right);
		else
			break ;
	}
	quick_sort_syms_ascii_reverse(syms, begin, right);
	quick_sort_syms_ascii_reverse(syms, right + 1, end);
}
