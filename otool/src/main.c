/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:09:42 by lperret           #+#    #+#             */
/*   Updated: 2018/04/30 11:26:53 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int			handle_arg(char *arg, t_infos infos)
{
	int				fd;
	char			*ptr;
	struct stat		buf;
	int				error;

	infos.filename = arg;
	if ((fd = open(arg, O_RDONLY)) < 0)
		return (handle_error(OPENING_ERROR, infos));
	else
	{
		if (fstat(fd, &buf) < 0)
			return (handle_error(FSTAT_ERROR, infos));
		if (buf.st_size == 0)
			return (handle_error(NOT_OBJECT_ERROR, infos));
		if ((ptr = mmap(0, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (handle_error(MMAP_ERROR, infos));
		infos.ptr = ptr;
		infos.filesize = buf.st_size;
		error = handle_error(otool(infos), infos);
		if (munmap(ptr, buf.st_size) < 0)
			handle_error(MUNMAP_ERROR, infos);
	}
	return (error);
}

static int			handle_args(int ac, char **av, t_infos infos)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (handle_arg(av[i], infos) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int					main(int ac, char **av)
{
	t_infos		infos;

	ft_bzero(&infos, sizeof(t_infos));
	infos.nbfiles = ac - 1;
	if (infos.nbfiles < 1)
		return (handle_error(NO_ARG_ERROR, infos));
	return (handle_args(ac, av, infos));
}
