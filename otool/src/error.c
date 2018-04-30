/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:00:37 by lperret           #+#    #+#             */
/*   Updated: 2018/04/30 13:54:23 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		handle_error(t_error error, t_infos infos)
{
	if (error && error && infos.filename)
	{
		(error == NOT_OBJECT_ERROR ? "" : ft_putstr_fd("'", 2));
		ft_putstr_fd(infos.filename, error == NOT_OBJECT_ERROR ? 1 : 2);
		(error == NOT_OBJECT_ERROR ? "" : ft_putstr_fd("'", 2));
		ft_putstr_fd(": ", error == NOT_OBJECT_ERROR ? 1 : 2);
	}
	if (error == NO_ARG_ERROR)
		ft_putendl_fd("ft_otool: at least one file must be specified", 2);
	else if (error == NOT_OBJECT_ERROR)
		ft_putendl_fd("is not an object file", 1);
	else if (error == OPENING_ERROR)
		ft_putendl_fd("Can't open file", 2);
	else if (error == FSTAT_ERROR)
		ft_putendl_fd("fstat failure", 2);
	else if (error == MMAP_ERROR)
		ft_putendl_fd("mmap failure", 2);
	else if (error == MUNMAP_ERROR)
		ft_putendl_fd("mummap failure", 2);
	else if (error == MALLOC_ERROR)
		ft_putendl_fd("malloc failure", 2);
	else if (error == FORMAT_ERROR)
		ft_putendl_fd("truncated or malformed object", 2);
	return (error == NOT_OBJECT_ERROR ? 0 : error);
}
