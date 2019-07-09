/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 19:30:30 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/29 22:32:41 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)((unsigned char *)s + i));
		i++;
	}
	return (NULL);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		value;
	size_t	i;

	value = 0;
	i = 0;
	while (value == 0 && i < n)
	{
		value += (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
		i++;
	}
	return (value);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (len == 0)
		return (dst);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
		}
	}
	else if (dst > src)
	{
		i = len - 1;
		while (1)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			if (i == 0)
				break ;
			i--;
		}
	}
	return (dst);
}

void	*ft_memdelr(void **ap)
{
	if (ap == NULL || *ap == NULL)
		return (NULL);
	free(*ap);
	*ap = NULL;
	return (NULL);
}

void	*ft_memdup(void *src, size_t len)
{
	void	*r;
	size_t	i;

	r = (void *)ft_memalloc(len + 1);
	if (r == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((char *)r)[i] = ((char *)src)[i];
		i++;
	}
	return (r);
}
