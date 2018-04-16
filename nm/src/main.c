#include "nm.h"

int			handle_arg(int nb_real_arg, char *arg, t_options options)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		ft_printf("%s: ", arg);
		return (handle_error(OPENING_ERROR));
	}
	else
	{
		if (nb_real_arg >= 2)
			ft_printf("\n%s:\n", arg);
		if (fstat(fd, &buf) < 0)
			return (handle_error(FSTAT_ERROR));
		else if ((ptr = mmap(0, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (handle_error(MMAP_ERROR));
		else
		{
			nm(ptr, arg, options);
			if (munmap(0, buf.st_size) < 0)
				handle_error(MUNMAP_ERROR);
		}
	}
	return (0);
}

int			handle_args(int ac, char **av, t_options options)
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

t_options	get_options(int ac, char **av)
{
	t_options	options;
	char		opt;
	int			i;

	ft_bzero(&options, sizeof(options));
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			continue;
		if (ft_strlen(av[i] + 1) > 1 || !ft_strstr(RECOGNIZED_OPTIONS, *(av + i) + 1))
			options.error = 1;
		else
		{
			opt = av[i][1];
			if (opt == 'g')
				options.g = 1;
			else if (opt == 'n' || opt == 'p' || opt == 'r')
				options.order = opt;
			else if (opt == 'u' || opt == 'U')
				options.undefined = opt;
			else
				options.j = 1;
		}
	}
	return options;
}

void		print_options(t_options options)
{
	ft_printf("options.error: %d\n", options.error);
	ft_printf("options.g: %d\n", options.g);
	ft_printf("options.order: %c\n", options.order);
	ft_printf("options.undefined: %c\n", options.undefined);
	ft_printf("options.j: %d\n", options.j);
}

int			main(int ac, char **av)
{
	t_options	options;

	options = get_options(ac, av);
	if (DEBUG)
		print_options(options);
	if (options.error)
		return (handle_error(UNRECOGNIZED_OPTION_ERROR));
	if (ac < 2)
		handle_arg(ac, "a.out", options);
	return (handle_args(ac, av, options));
}
