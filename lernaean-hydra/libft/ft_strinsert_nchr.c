/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert_nchr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:43:29 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/07 20:27:28 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_strinsert_nchr(char **str, char c, int index, int n)
{
	size_t	len;
	char	*new_str;
	int		i;

	if (str == NULL || *str == NULL || n <= 0 ||
			index < 0 || (size_t)index > (len = ft_strlen(*str)))
		return ;
	if (!(new_str = ft_strnew(len + n)))
		return ;
	i = -1;
	while (++i < index)
		new_str[i] = (*str)[i];
	i--;
	while (++i < index + n)
		new_str[i] = c;
	i--;
	while ((*str)[++i - n] != '\0')
		new_str[i] = (*str)[i - n];
	free(*str);
	*str = new_str;
}
