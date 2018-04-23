/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:57:33 by lperret           #+#    #+#             */
/*   Updated: 2018/04/23 20:12:04 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			handle_arg(int nb_real_arg, char *arg, t_options options)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(arg, O_RDONLY)) < 0)
		//return (handle_error(OPENING_ERROR, arg));
		return (handle_error(OPENING_ERROR, arg, nb_real_arg));
	else
	{
		//if (nb_real_arg >= 2)
		//	ft_printf("\n%s:\n", arg);
		if (fstat(fd, &buf) < 0)
			//return (handle_error(FSTAT_ERROR, arg));
			return (handle_error(FSTAT_ERROR, arg, nb_real_arg));
		if ((ptr = mmap(0, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			//return (handle_error(MMAP_ERROR, arg));
			return (handle_error(MMAP_ERROR, arg, nb_real_arg));
		if (DEBUG)
			ft_printf("buf.st_size: %u\n", buf.st_size);
		get_addr_max()[0] = (void*)ptr;
		get_addr_max()[1] = (void*)ptr + buf.st_size;
		if (DEBUG)
			ft_printf("addr_max: %p\n", *get_addr_max);
		handle_error(nm(ptr, arg, options, nb_real_arg), arg, nb_real_arg);
		if (munmap(0, buf.st_size) < 0)
			//handle_error(MUNMAP_ERROR, arg);
			handle_error(MUNMAP_ERROR, arg, nb_real_arg);
	}
	return (0);
}

static int			handle_args(int ac, char **av, t_options options)
{
	int		i;
	int		nb_real_arg;
	int		nb_errors;

	nb_errors = 0;
	i = 1;
	while (i < ac && av[i][0] == '-')
		i++;
	nb_real_arg = ac - i;
	while (i < ac)
	{
		if (av[i][0] == '-')
			;
		else if (handle_arg(nb_real_arg, av[i], options) != 0)
			nb_errors++;
		i++;
	}
	return (nb_errors > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}

static void			food_options(t_options *options, char *s)
{
	while (*s)
	{
		if (!ft_strchr(RECOGNIZED_OPTIONS, *s))
		{
			options->error = 1;
			return ;
		}
		else
		{
			if (*s == 'g')
				options->g = 1;
			else if (*s == 'n' || *s == 'p' || *s == 'r')
				options->order = *s;
			else if (*s == 'u' || *s == 'U')
				options->undef = *s;
			else
				options->j = 1;
		}
		s++;
	}
}

static t_options	get_options(int ac, char **av)
{
	t_options	options;
	int			i;

	ft_bzero(&options, sizeof(options));
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			continue;
		else
			food_options(&options, av[i] + 1);
	}
	return (options);
}

int					main(int ac, char **av)
{
	t_options	options;

	options = get_options(ac, av);
	if (options.error)
		return (handle_error(UNRECOGNIZED_OPTION_ERROR, NULL, 0));
	if (ac < 2)
		handle_arg(ac, "a.out", options);
	return (handle_args(ac, av, options));
}
