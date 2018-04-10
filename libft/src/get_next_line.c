/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:16:22 by lperret           #+#    #+#             */
/*   Updated: 2017/03/04 10:39:46 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_fd		*find_fd(t_fd **list_fd, int const fd)
{
	t_fd	*ptr;
	t_fd	*previous_ptr;

	if (fd < 0)
		return (NULL);
	ptr = *list_fd;
	previous_ptr = NULL;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		previous_ptr = ptr;
		ptr = ptr->next;
	}
	if (!(ptr = (t_fd *)malloc(sizeof(t_fd))))
		return (NULL);
	ptr->fd = fd;
	ptr->save = NULL;
	ptr->next = NULL;
	if (!(*list_fd))
		*list_fd = ptr;
	else
		previous_ptr->next = ptr;
	return (ptr);
}

static int		check_n_save(t_fd *block_fd, char **line)
{
	char	*ptr;

	if ((ptr = ft_strchr(block_fd->save, '\n')))
	{
		ptr[0] = '\0';
		if (!(*line = ft_strdup(block_fd->save)))
			return (-1);
		if (!(ptr = ft_strdup(ptr + 1)))
			return (-1);
		free(block_fd->save);
		block_fd->save = ptr;
		return (1);
	}
	return (0);
}

static int		check_n_buff(t_fd *block_fd, char **buff, char **line)
{
	char			*ptr;
	char			*tmp;

	if ((ptr = ft_strchr(*buff, '\n')))
	{
		ptr[0] = '\0';
		if (!(*line = ft_strjoin(block_fd->save, *buff)))
			return (-1);
		free(block_fd->save);
		if (!(block_fd->save = ft_strdup(ptr + 1)))
			return (-1);
		free(*buff);
		return (1);
	}
	if (!(tmp = ft_strjoin(block_fd->save, *buff)))
		return (-1);
	free(block_fd->save);
	block_fd->save = tmp;
	return (0);
}

static int		check_eof(t_fd *block_fd, char **buff,
		char **line, int ret)
{
	free(*buff);
	if (ret < 0)
		return (-1);
	if (block_fd->save && *block_fd->save == 0)
	{
		free(block_fd->save);
		block_fd->save = NULL;
	}
	if (block_fd->save == NULL)
	{
		free(block_fd);
		return (0);
	}
	if (!(*line = ft_strdup(block_fd->save)))
		return (-1);
	free(block_fd->save);
	block_fd->save = NULL;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		*buff;
	int			ret;
	static t_fd *list_fd = NULL;
	t_fd		*block_fd;

	ret = 0;
	block_fd = NULL;
	if (!(block_fd = find_fd(&list_fd, fd)))
		return (-1);
	if (block_fd->save)
	{
		if ((ret = check_n_save(block_fd, line) || ret == -1))
			return (ret);
	}
	else
		block_fd->save = ft_strnew(0);
	if (!(block_fd->save) || !(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((ret = read(block_fd->fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((ret = check_n_buff(block_fd, &buff, line) || ret == -1))
			return (ret);
	}
	return (check_eof(block_fd, &buff, line, ret));
}
