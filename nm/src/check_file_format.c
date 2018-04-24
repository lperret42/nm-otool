#include "nm.h"

void		**get_addr_max(void)
{
	static void		*addr_ext[2] = {NULL, NULL};  //addr_ext[0] = ptr
												  //addr_ext[1] = ptr + sizeof(file)

	return (addr_ext);
}

int			check_addr(void **dst, void *src, size_t size)
{
	void	**addr_ext;

	addr_ext = get_addr_max();
	if (DEBUG)
	{
		ft_printf("addr_ext[0]: %p\n", addr_ext[0]);
		ft_printf("addr + size: %p\n", (void*)(src + size));
		ft_printf("addr_ext[1]: %p\n", addr_ext[1]);
	}
	if (!(src + size >= addr_ext[0] && src + size <= addr_ext[1]))
		return (-1);
	if (dst != NULL)
		*dst = src;
	return (0);
}

t_glob		*glob(void)
{
	static t_glob	glob;

	return (&glob);
}
