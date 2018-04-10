#include "otool.h"

void		otool(char *ptr)
{
	ptr = NULL;
	ft_printf("yo\n");
}

int			main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (ac != 2)
	{
		ft_printf("Please give me an argument\n");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_printf("open failure\n");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_printf("fstat failure\n");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("mmap failure\n");
		return (EXIT_FAILURE);
	}
	otool(ptr);
	if (munmap(0, buf.st_size) < 0)
	{
		ft_printf("mummap failure\n");
		return (EXIT_FAILURE);
	}
	return 0;
}
