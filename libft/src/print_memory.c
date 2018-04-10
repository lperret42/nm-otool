/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:47:45 by lperret           #+#    #+#             */
/*   Updated: 2017/01/11 18:16:27 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_printable(unsigned char c)
{
	if (c > 31 && c < 127)
		ft_putchar(c);
	else
		ft_putchar('.');
}

void	print_hexa(unsigned char c)
{
	char *tab;

	tab = "0123456789abcdef";
	ft_putchar(tab[c / 16]);
	ft_putchar(tab[c % 16]);
}

void	everything(char *work, size_t start, size_t size)
{
	size_t i;

	i = start;
	while ((i < (start + 16)) && i < size)
	{
		print_hexa(work[i]);
		if (i % 2)
			ft_putchar(' ');
		i++;
	}
	while (i < (start + 16))
	{
		ft_putchar(' ');
		ft_putchar(' ');
		if (i % 2)
			ft_putchar(' ');
		i++;
	}
	i = start;
	while ((i < start + 16) && i < size)
	{
		print_printable(work[i]);
		i++;
	}
	ft_putchar('\n');
}

void	print_memory(const void *addr, size_t size)
{
	char		*work;
	size_t		start;

	work = (char *)addr;
	start = 0;
	while (start < size)
	{
		everything(work, start, size);
		start += 16;
	}
}
