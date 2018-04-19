#include "otool.h"

static int			handle_arg(int nb_real_arg, char *arg)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(arg, O_RDONLY)) < 0)
		return (handle_error(OPENING_ERROR, arg));
	else
	{
		//if (nb_real_arg >= 2)
		//	ft_printf("\n%s:\n", arg);
		nb_real_arg = -550000514;
		ft_printf("%s:\n", arg);
		if (fstat(fd, &buf) < 0)
			return (handle_error(FSTAT_ERROR, arg));
		else if ((ptr = mmap(0, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (handle_error(MMAP_ERROR, arg));
		else
		{
			handle_error(otool(ptr, arg), arg);
			if (munmap(0, buf.st_size) < 0)
				handle_error(MUNMAP_ERROR, arg);
		}
	}
	return (0);
}

static int			handle_args(int ac, char **av)
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
		else if (handle_arg(nb_real_arg, av[i]) != 0)
			nb_errors++;
		i++;
	}
	return (nb_errors > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	if (ac < 2)
		return (handle_error(NO_ARG_ERROR, NULL));
	return (handle_args(ac, av));
}
