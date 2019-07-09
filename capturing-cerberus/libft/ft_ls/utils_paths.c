/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:49:48 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 19:00:01 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls.h"

char		*ft_prepend_path(char const *dirpath, char const *filename)
{
	char			*r;
	unsigned int	i;
	size_t			len_s1;
	size_t			len_s2;

	if (!dirpath || !filename)
		return (NULL);
	len_s1 = ft_strlen(dirpath);
	len_s2 = ft_strlen(filename);
	if ((r = (char *)malloc(len_s1 + len_s2 + 2)) == NULL)
		return (NULL);
	r[len_s1 + len_s2 + 1] = '\0';
	i = 0;
	while (i < len_s1)
	{
		r[i] = dirpath[i];
		i++;
	}
	r[i++] = '/';
	while (i - len_s1 <= len_s2)
	{
		r[i] = filename[i - len_s1 - 1];
		i++;
	}
	return (r);
}

char		*ft_basename(char const *path)
{
	unsigned int		i;
	size_t				len;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	len = (size_t)i;
	while (i > 0 && path[i] != '/')
		i--;
	if (path[i] == '/')
		return (ft_strsub(path, i + 1, len - i));
	return (ft_strdup(path));
}
