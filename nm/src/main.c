#include "nm.h"

int			handle_arg(int ac, char *arg)
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
		if (ac >= 3)
			ft_printf("\n%s:\n", arg);
		if (fstat(fd, &buf) < 0)
			return (handle_error(FSTAT_ERROR));
		else if ((ptr = mmap(0, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (handle_error(MMAP_ERROR));
		else
		{
			nm(ptr, arg);
			if (munmap(0, buf.st_size) < 0)
				handle_error(MUNMAP_ERROR);
		}
	}
	return (0);
}

int			handle_args(int ac, char **av)
{
	int		i;
	int		nb_errors;

	nb_errors = 0;
	i = 1;
	while (i < ac)
	{
		if (handle_arg(ac, av[i]) != 0)
			nb_errors++;
		i++;
	}
	return (nb_errors > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	if (ac < 2)
		handle_arg(ac, "a.out");
	return (handle_args(ac, av));
}
