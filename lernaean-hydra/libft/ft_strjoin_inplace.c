/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_inplace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 23:55:30 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 00:37:03 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	ft_strjoin_inplace(char **s1, char const *s2)
{
	char *r;

	if (s1 == NULL || *s1 == NULL || s2 == NULL)
		return ;
	r = ft_strjoin(*s1, s2);
	if (!r)
		return ;
	free(*s1);
	*s1 = r;
}
