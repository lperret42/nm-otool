#include "nm.h"

int			check_addr(void **dst, void *src, size_t size, t_infos infos)
{
	if (!(src >= (void*)infos.ptr && src <= (void*)infos.ptr + infos.filesize &&
		src + size >= (void*)infos.ptr &&
						src + size <= (void*)infos.ptr + infos.filesize))
		return (-1);
	if (dst != NULL)
		*dst = src;
	return (0);
}

int			check_sym_name(char *name, t_infos infos)
{
	if ((void*)name < (void*)infos.ptr)
		return (1);
	while ((void*)name <= (void*)infos.ptr + infos.filesize)
		if (!*name++)
			return (0);
	return (1);
}
