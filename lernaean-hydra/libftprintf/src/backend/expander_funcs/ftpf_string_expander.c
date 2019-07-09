/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_string_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:00:49 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/07 22:06:29 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_backend.h"

/*
** -----------------------------------------------------------------------------
**                             ftpf_string_expander
** -----------------------------------------------------------------------------
**   specifier:    %s
**   description:  writes a string
**   options:      0,-,field_width,.
**   notes:        none
** -----------------------------------------------------------------------------
**                             general reminders
** -----------------------------------------------------------------------------
**   An expander function writes with ft_mswriten(md->ms, "...", 1)
**   and returns the number of characters written.
**   It writes one character at a time only if md->len +written < md->max_len
**   If it needs to retrieve data, it uses md->args, which is a copy of the
**   initial state of the variadic arguments list. Always make a copy first.
**   md->ex is the expandler that holds all the option flags.
**   Expander functions must not modify md->i. (TODO: take i out of md)
**   Expander functions must update md->next_arg_num if they access data.
** -----------------------------------------------------------------------------
*/

static char	*get_arg(t_ftpf_master_data *md)
{
	va_list	args_copy;
	short	arg_num;
	short	i;
	char	*ret;

	va_copy(args_copy, md->args);
	arg_num = (md->ex->arg_num < 0 ? md->next_arg_num : md->ex->arg_num);
	md->next_arg_num = arg_num + 1;
	i = 0;
	while (i++ < arg_num)
		ret = va_arg(args_copy, char *);
	va_end(args_copy);
	return (ret);
}

static int	determine_padding(t_ftpf_master_data *md, char *pad_char, char *str)
{
	int		str_len;

	if (md->ex->field_width == 0)
		return (0);
	if (md->ex->lfjusty)
		*pad_char = ' ';
	else
		*pad_char = md->ex->zpad ? '0' : ' ';
	str_len = ft_strlen(str);
	if (md->ex->precision >= 0 && str_len > md->ex->precision)
		str_len = md->ex->precision;
	return (md->ex->field_width - str_len);
}

static int	handle_padding(t_ftpf_master_data *md,
		int before_or_after, char *str)
{
	char	padchar;
	int		padding;

	padding = determine_padding(md, &padchar, str);
	if (before_or_after == 0)
	{
		if (padding > 0 && !(md->ex->lfjusty))
			ft_msputnchar(md->ms, padchar, padding);
	}
	else if (before_or_after == 1)
	{
		if (padding > 0 && (md->ex->lfjusty))
			ft_msputnchar(md->ms, padchar, padding);
	}
	return (padding);
}

int			ftpf_string_expander(t_ftpf_master_data *md)
{
	int		written;
	char	*str;
	int		i;

	written = 0;
	str = get_arg(md);
	handle_padding(md, 0, str);
	i = 0;
	while (str[i] && (md->ex->precision < 0 || written < md->ex->precision)
			&& (md->max_len < 0 || md->len + written < md->max_len))
	{
		ft_mswriten(md->ms, str + i, 1);
		written++;
		i++;
	}
	if (handle_padding(md, 1, str) > 0)
		written += handle_padding(md, -1, str);
	return (written);
}
