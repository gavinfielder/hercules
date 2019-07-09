/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_unsigned_int_expander.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:58:56 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/07 22:07:01 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_backend.h"

/*
** -----------------------------------------------------------------------------
**                             ftpf_unsigned_int_expander
** -----------------------------------------------------------------------------
**   specifier:    %u
**   description:  writes an unsigned integer
**   options:      #,0,-,+,' ',field_width,.,hh,h,l,ll
**   notes:        none
** -----------------------------------------------------------------------------
**                             general reminders
** -----------------------------------------------------------------------------
**   An expander function writes with ft_mswriten(md->ms, "...", 1)
**   and returns the number of characters written.
**   It writes one character at a time only if md->len + written < md->max_len
**   If it needs to retrieve data, it uses md->args, which is a copy of the
**   initial state of the variadic arguments list. Always make a copy first.
**   md->ex is the expandler that holds all the option flags.
**   Expander functions must not modify md->i. (TODO: take i out of md)
**   Expander functions must update md->next_arg_num if they access data.
** -----------------------------------------------------------------------------
*/

int								ftpf_unsigned_int_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[UINT]");
	return (6);
}
