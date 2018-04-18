/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:07:03 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 11:07:09 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_error(t_error error, char *file)
{
	if (error && file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error == UNRECOGNIZED_OPTION_ERROR)
		ft_putendl_fd("Unrecognized option.", 2);
	else if (error == NOT_OBJECT_ERROR)
		ft_putendl_fd("The file was not recognized as a valid object file.\n", 2);
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
