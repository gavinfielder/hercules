/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unimplemented_expanders_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:44:38 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/07 22:07:17 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_backend.h"

/*
** -----------------------------------------------------------------------------
**                             title
** -----------------------------------------------------------------------------
**   specifier:    .
**   description:  .
**   options:      .
**   notes:        .
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

int								ftpf_hexlower_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[HEXL]");
	return (6);
}

int								ftpf_hexupper_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[HEXU]");
	return (6);
}

int								ftpf_float_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[FLOAT]");
	return (7);
}

int								ftpf_binary_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[BINY]");
	return (6);
}

int								ftpf_memory_expander(
									t_ftpf_master_data *md)
{
	ft_mswrite(md->ms, "[MEM]");
	return (5);
}
