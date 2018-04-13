#include "nm.h"

void swap(t_ar *ars, int a, int b)
{
	t_ar	tmp;

	tmp = ars[a];
	ars[a] = ars[b];
	ars[b] = tmp;
}

void quick_sort(t_ar *ars, int begin, int end)
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
			swap(ars, left, right);
		else break;
	}

	quick_sort(ars, begin, right);
	quick_sort(ars, right + 1, end);
}
