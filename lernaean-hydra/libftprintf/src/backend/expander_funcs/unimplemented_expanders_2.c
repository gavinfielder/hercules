/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unimplemented_expanders_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:48:15 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/07 22:07:27 by gfielder         ###   ########.fr       */
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
**   An expander function writes with ft_mswrite(md->ms, "...")
**   and returns the number of characters written.
**   It writes one character at a time only if md->len + written < md->max_len
**   If it needs to retrieve data, it uses md->args, which is a copy of the
**   initial state of the variadic arguments list. Always make a copy first.
**   md->ex is the expandler that holds all the option flags.
**   Expander functions must not modify md->i. (TODO: take i out of md)
**   Expander functions must update md->next_arg_num if they access data.
** -----------------------------------------------------------------------------
*/

int								ftpf_ptr_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[PTR]");
	return (5);
}

int								ftpf_char_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[CHAR]");
	return (6);
}

int								ftpf_octal_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[OCT]");
	return (5);
}
