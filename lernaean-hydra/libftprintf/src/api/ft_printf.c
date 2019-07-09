/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:25:25 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 13:30:00 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ftpf_backend.h"

int		ft_printf(const char *fmt, ...)
{
	va_list			args;
	int				ret_val;

	va_start(args, fmt);
	ret_val = ft_vdprintf(0, fmt, args);
	va_end(args);
	return (ret_val);
}
