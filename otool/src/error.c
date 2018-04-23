/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:00:37 by lperret           #+#    #+#             */
/*   Updated: 2018/04/23 15:00:50 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		handle_error(t_error error, char *file)
{
	if (error && file)
	{
		ft_putstr_fd(file, 1);
		ft_putstr_fd(": ", 1);
	}
	if (error == NO_ARG_ERROR)
		ft_putendl_fd("at least one file must be specified", 2);
	else if (error == NOT_OBJECT_ERROR)
		ft_putendl_fd("is not an object file", 1);
	else if (error == OPENING_ERROR)
		ft_putendl_fd("Can't open file.", 2);
	else if (error == FSTAT_ERROR)
		ft_putendl_fd("fstat failure.", 2);
	else if (error == MMAP_ERROR)
		ft_putendl_fd("mmap failure.", 2);
	else if (error == MUNMAP_ERROR)
		ft_putendl_fd("mummap failure.", 2);
	else if (error == MALLOC_ERROR)
		ft_putendl_fd("malloc failure.", 2);
	return (error);
}
