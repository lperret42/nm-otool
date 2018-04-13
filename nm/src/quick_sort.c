#include "nm.h"

void swap(t_ar *ars, int a, int b)
{
    t_ar	temp = ars[a];

	ars[a] = ars[b];
    ars[b] = temp;
}

void quick_sort(t_ar *ars, int debut, int fin)
{
    int left = debut-1;
    int right = fin+1;

	const uint64_t pivot = ars[debut].strx;

    if(debut >= fin)
        return;

    while(1)
    {
        do right--; while(ars[right].strx > pivot);
        do left++; while(ars[left].strx < pivot);

        if(left < right)
            swap(ars, left, right);
        else break;
    }

    quick_sort(ars, debut, right);
    quick_sort(ars, right+1, fin);
}
