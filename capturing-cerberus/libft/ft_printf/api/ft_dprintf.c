/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:57:02 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/29 18:57:47 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ftpf_backend.h"
#include "libftprintf.h"

int		ft_dprintf(int fd, const char *fmt, ...)
{
	va_list			args;
	int				ret_val;

	va_start(args, fmt);
	ret_val = ft_vdprintf(fd, fmt, args);
	va_end(args);
	return (ret_val);
}
