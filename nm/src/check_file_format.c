#include "nm.h"

int			check_addr(void **dst, void *src, size_t size, t_infos infos)
{
	if (DEBUG)
	{
		ft_printf("infos.ptr:                  %p\n", infos.ptr);
		ft_printf("addr + size:                %p\n", (void*)(src + size));
		ft_printf("infos.ptr + infos.filesize: %p\n", infos.ptr + infos.filesize);
	}
	if (!(src + size >= (void*)infos.ptr &&
						src + size <= (void*)infos.ptr + infos.filesize))
		return (-1);
	if (dst != NULL)
		*dst = src;
	return (0);
}
