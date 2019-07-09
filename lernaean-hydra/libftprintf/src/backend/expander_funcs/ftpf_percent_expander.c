/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_percent_expander.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:26:59 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 22:49:50 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_backend.h"

/*
** -----------------------------------------------------------------------------
**                             ftpf_percent_expander
** -----------------------------------------------------------------------------
**   specifier:    %%
**   description:  writes a '%'
**   options:      no options
**   notes:        Uses no arguments from the va_list args.
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

int								ftpf_percent_expander(
									t_ftpf_master_data *md)
{
	if (md->max_len >= 0 && md->len < md->max_len)
	{
		ft_mswrite(md->ms, "%");
		md->len = md->len + 1;
		return (1);
	}
	return (0);
}
