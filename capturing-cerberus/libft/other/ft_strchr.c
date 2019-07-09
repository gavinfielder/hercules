/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:27:59 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 07:37:02 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

int		ft_strchr_idx(const char *s, int c)
{
	char	*p;

	if (!s)
		return (-1);
	p = ft_strchr(s, c);
	if (!p)
		return (-1);
	return ((int)(p - s));
}

int		ft_strchr_idx_any(const char *s, const char *any)
{
	int		min;
	int		tmp;
	int		i;

	min = -1;
	i = 0;
	while (any[i])
	{
		tmp = ft_strchr_idx(s, any[i]);
		if (min == -1 || (tmp != -1 && tmp < min))
			min = tmp;
		i++;
	}
	return (min);
}
