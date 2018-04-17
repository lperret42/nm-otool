/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_syms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:10:36 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 15:00:27 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	quick_sort_syms_numerically(t_sym *syms, int begin, int end)
{
	int			left;
	int			right;
	long		pivot;

	left = begin - 1;
	right = end + 1;
	pivot = syms[begin].value;
	if (begin >= end)
		return ;
	while (1)
	{
		while (syms[--right].value > pivot)
			;
		while (syms[++left].value < pivot)
			;
		if (left < right)
			swap_sym(syms, left, right);
		else
			break ;
	}
	quick_sort_syms_numerically(syms, begin, right);
	quick_sort_syms_numerically(syms, right + 1, end);
}

void	quick_sort_syms_numerically_reverse(t_sym *syms, int begin, int end)
{
	int			left;
	int			right;
	long		pivot;

	left = begin - 1;
	right = end + 1;
	pivot = syms[begin].value;
	if (begin >= end)
		return ;
	while (1)
	{
		while (syms[--right].value < pivot)
			;
		while (syms[++left].value > pivot)
			;
		if (left < right)
			swap_sym(syms, left, right);
		else
			break ;
	}
	quick_sort_syms_numerically_reverse(syms, begin, right);
	quick_sort_syms_numerically_reverse(syms, right + 1, end);
}

void	quick_sort_syms_ascii(t_sym *syms, int begin, int end)
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
		while (ft_strcmp(syms[++left].name, pivot) < 0)
			;
		while (ft_strcmp(syms[--right].name, pivot) > 0)
			;
		if (left < right)
			swap_sym(syms, left, right);
		else
			break ;
	}
	quick_sort_syms_ascii(syms, begin, right);
	quick_sort_syms_ascii(syms, right + 1, end);
}

void	quick_sort_syms_same_ascii_numerically(t_sym *syms, int nsyms, char r)
{
	int			i;
	int			begin;
	char		*tmp;

	if (DEBUG)
		ft_printf("debut quick_sort_syms_same_ascii_numerically\n");
	tmp = NULL;
	i = 0;
	while (i < nsyms)
	{
		/*
		if (DEBUG)
		{
			ft_printf("i: %d\n", i);
			ft_printf("tmp: %s\n", tmp);
			ft_printf("syms[i].name: %s\n", syms[i].name);
		}
		*/
		if (tmp && !syms[i].for_debug && !ft_strcmp(tmp, syms[i].name))
		{
			if (DEBUG)
				ft_printf("nsyms: %d\n", nsyms);
			begin = i - 1;
			//while (!ft_strcmp(tmp, syms[i].name) && i < nsyms)
			while (i < nsyms && !ft_strcmp(tmp, syms[i].name))
			{
				if (DEBUG)
					ft_printf("i: %d\n", i);
				i++;
			}
			if (DEBUG)
				ft_printf("yo2\n");
			if (DEBUG)
			{
				ft_printf("begin: %d\n", begin);
				ft_printf("i: %d\n", i);
			}
			if (r == 'n')
				quick_sort_syms_numerically(&(syms[begin]), 0, i - begin - 1);
			else
				quick_sort_syms_numerically_reverse(&(syms[begin]), 0,
														i - begin - 1);
		}
		tmp = syms[i].for_debug ? NULL : syms[i].name;
		i++;
	}
}

void	quick_sort_syms(t_sym *syms, int nsyms, t_options options)
{
	int		i;

	if (options.order == 'p')
		return ;
	else if (!options.order)
	{
		if (DEBUG)
			ft_printf("before ascii\n");
		quick_sort_syms_ascii(syms, 0, nsyms - 1);
		if (DEBUG)
		{
			ft_printf("after ascii\n");
			ft_printf("before quick_sort_syms_same_ascii_numerically\n");
		}
		quick_sort_syms_same_ascii_numerically(syms, nsyms, 'n');
		if (DEBUG)
			ft_printf("after quick_sort_syms_same_ascii_numerically\n");
	}
	else if (options.order == 'n')
	{
		quick_sort_syms_numerically(syms, 0, nsyms - 1);
		i = 0;
		while (syms[i].value < 0)
			i++;
		if (i >= 2)
			quick_sort_syms_ascii(syms, 0, i - 1);
	}
	else if (options.order == 'r')
	{
		if (DEBUG)
			ft_printf("before ascii reverse\n");
		quick_sort_syms_ascii_reverse(syms, 0, nsyms - 1);
		if (DEBUG)
		{
			ft_printf("after ascii reverse\n");
			ft_printf("before quick_sort_syms_same_ascii_numerically\n");
		}
		quick_sort_syms_same_ascii_numerically(syms, nsyms, 'r');
		if (DEBUG)
			ft_printf("after quick_sort_syms_same_ascii_numerically\n");
	}
}
