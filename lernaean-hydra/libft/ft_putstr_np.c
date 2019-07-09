/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_np.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:32:50 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/06 10:34:38 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_putstr_np(char const *str, char c_if_nonprintable)
{
	int i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_np(str[i], c_if_nonprintable);
		i++;
	}
}
