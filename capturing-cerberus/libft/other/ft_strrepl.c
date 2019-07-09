/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:53:16 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/29 20:20:52 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			ft_strrepl(char **str, unsigned int start, size_t len,
				const char *with)
{
	size_t	ret_len;
	size_t	with_len;
	char	*ret;

	if (!str || !(*str) || !with)
		return (-1);
	with_len = ft_strlen(with);
	ret_len = ft_strlen(*str) + with_len - len;
	if ((ret = ft_strnew(ret_len)) == NULL)
		return (-1);
	ft_memcpy(ret, *str, start);
	ft_memcpy(ret + start, with, with_len);
	ft_strcpy(ret + start + with_len, *str + start + len);
	free(*str);
	*str = ret;
	return (1);
}
