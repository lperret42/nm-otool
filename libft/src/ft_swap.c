/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:38:27 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:38:29 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b)
{
	unsigned char c;

	c = *(unsigned char *)a;
	*(unsigned char *)a = *(unsigned char *)b;
	*(unsigned char *)b = c;
}
