/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:00:00 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 15:00:12 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ftpf_backend.h"

int		ft_snprintf(char *buff, size_t size, const char *fmt, ...)
{
	va_list			args;
	int				ret_val;

	if (buff == NULL)
		return (-1);
	va_start(args, fmt);
	ret_val = ft_vsnprintf(buff, size, fmt, args);
	va_end(args);
	return (ret_val);
}
