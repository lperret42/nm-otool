/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:09:50 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 11:18:25 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void		swap_ar(t_ar *ars, int a, int b)
{
	t_ar	tmp;

	tmp = ars[a];
	ars[a] = ars[b];
	ars[b] = tmp;
}

void			quick_sort_ars(t_ar *ars, int begin, int end)
{
	int			left;
	int			right;
	uint64_t	pivot;

	left = begin - 1;
	right = end + 1;
	pivot = ars[begin].strx;
	if (begin >= end)
		return ;
	while (1)
	{
		while (ars[--right].strx > pivot)
			;
		while (ars[++left].strx < pivot)
			;
		if (left < right)
			swap_ar(ars, left, right);
		else
			break ;
	}
	quick_sort_ars(ars, begin, right);
	quick_sort_ars(ars, right + 1, end);
}
