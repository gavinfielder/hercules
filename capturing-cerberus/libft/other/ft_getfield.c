/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfield.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 15:26:49 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/17 15:34:10 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_getfield(const char *str, int fieldno, const char *delims)
{
	char	**split;
	int		number_fields;
	char	*ret;

	ret = NULL;
	split = ft_strsplit(str, delims);
	number_fields = 0;
	while (split[number_fields])
		number_fields++;
	if (fieldno >= 0 && fieldno < number_fields)
		ret = ft_strdup(split[fieldno]);
	ft_destroy_nullterm_ptrarray((void ***)&split);
	return (ret);
}
