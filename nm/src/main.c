/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:57:33 by lperret           #+#    #+#             */
/*   Updated: 2018/04/25 13:49:21 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			handle_arg(char *arg, t_infos infos)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(arg, O_RDONLY)) < 0)
		return (handle_error(OPENING_ERROR, arg, infos.nbfiles));
	else
	{
		if (fstat(fd, &buf) < 0)
			return (handle_error(FSTAT_ERROR, arg, infos.nbfiles));
		if ((ptr = mmap(0, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (handle_error(MMAP_ERROR, arg, infos.nbfiles));
		if (DEBUG)
			ft_printf("buf.st_size: %u\n", buf.st_size);
		infos.filename = arg;
		infos.ptr = ptr;
		infos.filesize = buf.st_size;
		handle_error(nm(infos), arg, infos.nbfiles);
		if (munmap(ptr, buf.st_size) < 0)
			handle_error(MUNMAP_ERROR, arg, infos.nbfiles);
	}
	return (0);
}

static int			handle_args(int ac, char **av, t_infos infos)
{
	int		i;
	int		nb_errors;

	nb_errors = 0;
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
			;
		else if (handle_arg(av[i], infos) != 0)
			nb_errors++;
		i++;
	}
	return (nb_errors > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}

static void			food_flags(char *s, t_infos *infos)
{
	while (*s)
	{
		if (!ft_strchr(RECOGNIZED_OPTIONS, *s))
		{
			infos->flags.error = 1;
			return ;
		}
		else
		{
			if (*s == 'g')
				infos->flags.g = 1;
			else if (*s == 'n' || *s == 'p' || *s == 'r')
				infos->flags.order = *s;
			else if (*s == 'u' || *s == 'U')
				infos->flags.undef = *s;
			else
				infos->flags.j = 1;
		}
		s++;
	}
}

static void		get_flags(int ac, char **av, t_infos *infos)
{
	int			i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			infos->nbfiles += 1;
		else
			food_flags(av[i] + 1, infos);
	}
}

int					main(int ac, char **av)
{
	t_infos		infos;

	ft_bzero(&infos, sizeof(t_infos));
	get_flags(ac, av, &infos);
	if (infos.flags.error)
		return (handle_error(UNRECOGNIZED_OPTION_ERROR, NULL, 0));
	if (infos.nbfiles == 0)
		handle_arg("a.out", infos);
	return (handle_args(ac, av, infos));
}
