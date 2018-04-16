#include "nm.h"

void		print_syms(t_sym *syms, int nsyms)
{
	int		i;

	i = 0;
	while (i < nsyms)
	{
		if (syms[i].name && !syms[i].for_debug)
		{
			if (syms[i].n_sect != NO_SECT)
				ft_printf("%016lx", syms[i].value);
			else
				ft_printf("%s", "                ");
			ft_printf(" ");
			ft_printf("%c", syms[i].letter);
			ft_printf(" ");
			ft_printf("%s\n", syms[i].name);
		}
		i++;
	}
}
