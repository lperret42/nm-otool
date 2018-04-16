#include "nm.h"

void swap_ar(t_ar *ars, int a, int b)
{
	t_ar	tmp;

	tmp = ars[a];
	ars[a] = ars[b];
	ars[b] = tmp;
}


void swap_sym(t_sym *syms, int a, int b)
{
	t_sym	tmp;

	tmp = syms[a];
	syms[a] = syms[b];
	syms[b] = tmp;
}

void quick_sort_ars(t_ar *ars, int begin, int end)
{
	int			left;
	int			right;
	uint64_t	pivot;

	left = begin - 1;
	right = end + 1;
	pivot = ars[begin].strx;
	if(begin >= end)
		return;
	while(1)
	{
		do right--; while(ars[right].strx > pivot);
		do left++; while(ars[left].strx < pivot);

		if(left < right)
			swap_ar(ars, left, right);
		else break;
	}

	quick_sort_ars(ars, begin, right);
	quick_sort_ars(ars, right + 1, end);
}

void quick_sort_syms_numerically(t_sym *syms, int begin, int end)
{
	int			left;
	int			right;
	long		pivot;

	left = begin - 1;
	right = end + 1;
	pivot = syms[begin].value;
	if(begin >= end)
		return;
	while(1)
	{
		do right--; while(syms[right].value > pivot);
		do left++; while(syms[left].value < pivot);

		if(left < right)
			swap_sym(syms, left, right);
		else break;
	}

	quick_sort_syms_numerically(syms, begin, right);
	quick_sort_syms_numerically(syms, right + 1, end);
}

void quick_sort_syms_same_ascii_numerically(t_sym *syms, int nsyms)
{
	int			i;
	int			begin;
	char		*tmp;

	tmp = NULL;
	i = 0;
	while (i < nsyms)
	{
		if (tmp && !ft_strcmp(tmp, syms[i].name))
		{
			begin = i - 1;
			while (!ft_strcmp(tmp, syms[i].name) && i < nsyms)
				i++;
			quick_sort_syms_numerically(&(syms[begin]), 0, i - begin - 1);
			tmp = syms[i++].name;
		}
		else
			tmp = syms[i++].name;
	}
}

void		quick_sort_syms_ascii(t_sym *syms, int begin, int end)
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

void		quick_sort_syms(t_sym *syms, int nsyms, t_options options)
{
	int		i;

	if (options.order == 'p')
		return ;
	else if (!options.order)
	{
		quick_sort_syms_ascii(syms, 0, nsyms - 1);
		quick_sort_syms_same_ascii_numerically(syms, nsyms);
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
		quick_sort_syms_numerically(syms, 0, nsyms - 1);  // need to reverse
}
