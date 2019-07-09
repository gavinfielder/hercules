/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_signed_int_expander.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:53:04 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/07 22:04:30 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_backend.h"

/*
** -----------------------------------------------------------------------------
**                             ftpf_signed_int_expander
** -----------------------------------------------------------------------------
**   specifier:    %d, %i
**   description:  writes a signed integer
**   options:      0,-,+,' ',field_width,.,hh,h,l,ll
**   notes:        precision means minimum digits (left pad with zero)
** -----------------------------------------------------------------------------
**                             general reminders
** -----------------------------------------------------------------------------
**   An expander function writes with ft_mswriten(md->ms, "...", 1)
**   and returns the number of characters written.
**   It writes one character at a time only if md->len (+written) < md->max_len
**   If it needs to retrieve data, it uses md->args, which is a copy of the
**   initial state of the variadic arguments list. Always make a copy first.
**   md->ex is the expandler that holds all the option flags.
**   Expander functions must not modify md->i. (TODO: take i out of md)
**   Expander functions must update md->next_arg_num if they access data.
** -----------------------------------------------------------------------------
*/

/*
** This array of function pointers is indexed in with expandler.size_mod
*/
const static t_ftpf_sint_ga	g_sint_getarg[] =
{
	ftpf_sint_get_arg_4,
	ftpf_sint_get_arg_4,
	ftpf_sint_get_arg_4,
	ftpf_sint_get_arg_8,
	ftpf_sint_get_arg_8,
	ftpf_sint_get_arg_8
};

int							ftpf_signed_int_expander(t_ftpf_master_data *md)
{
	char		*str;
	long long	value;
	int			i;

	value = g_sint_getarg[md->ex->size_mod](md);
	str = ft_litoa(value);
	ftpf_handle_padding_sint(md, &str);
	i = 0;
	while (str[i] && (md->max_len < 0 || md->len + i < md->max_len))
	{
		ft_mswriten(md->ms, str + i, 1);
		i++;
	}
	return (i);
}
