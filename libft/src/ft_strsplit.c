/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:05:38 by lperret           #+#    #+#             */
/*   Updated: 2017/03/10 18:42:57 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_word(char const *s, char c)
{
	int		word_ok;
	int		count;

	word_ok = 1;
	count = 0;
	while (*s)
	{
		if (word_ok && *s != c)
		{
			count++;
			word_ok = 0;
		}
		else if (*s == c)
			word_ok = 1;
		s++;
	}
	return (count);
}

static int		ft_strlen_fd(char const *s, char c)
{
	int		length;

	length = 0;
	while (*s != c && *s)
	{
		length++;
		s++;
	}
	return (length);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		nbr_word;
	char	**av;

	i = 0;
	if (!s)
		return (NULL);
	nbr_word = ft_count_word(s, c);
	if (!(av = (char**)malloc(sizeof(*av) * (nbr_word + 1))))
		return (NULL);
	while (i < nbr_word)
	{
		while (*s == c)
			s++;
		if (!(av[i] = ft_strsub(s, 0, ft_strlen_fd(s, c))))
			return (NULL);
		s = s + ft_strlen_fd(s, c);
		i++;
	}
	av[i] = NULL;
	return (av);
}
