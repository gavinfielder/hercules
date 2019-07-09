/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_signed_int_expander_aux.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:37:56 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/07 22:02:00 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_backend.h"

long long	ftpf_sint_get_arg_4(t_ftpf_master_data *md)
{
	va_list		args_copy;
	short		arg_num;
	short		i;
	int			ret;

	va_copy(args_copy, md->args);
	arg_num = (md->ex->arg_num < 0 ? md->next_arg_num : md->ex->arg_num);
	md->next_arg_num = arg_num + 1;
	i = 0;
	while (i++ < arg_num)
		ret = va_arg(args_copy, int);
	va_end(args_copy);
	return ((long long)ret);
}

long long	ftpf_sint_get_arg_8(t_ftpf_master_data *md)
{
	va_list		args_copy;
	short		arg_num;
	short		i;
	long long	ret;

	va_copy(args_copy, md->args);
	arg_num = (md->ex->arg_num < 0 ? md->next_arg_num : md->ex->arg_num);
	md->next_arg_num = arg_num + 1;
	i = 0;
	while (i++ < arg_num)
		ret = va_arg(args_copy, long long);
	va_end(args_copy);
	return (ret);
}

void		ftpf_handle_padding_sint(t_ftpf_master_data *md, char **str)
{
	size_t	str_len;
	int		sign;

	sign = (((*str)[0] == '-' || md->ex->allsign) ? 1 : 0);
	if ((*str)[0] != '-' && sign)
		ft_strinsert_nchr(str, '+', 0, 1);
	str_len = ft_strlen(*str);
	if (md->ex->precision > 0)
	{
		ft_strinsert_nchr(str, '0', sign, md->ex->precision - str_len + sign);
		str_len = ft_strlen(*str);
	}
	if (md->ex->field_width > 0)
	{
		if (!(md->ex->lfjusty) && md->ex->zpad && (md->ex->precision <= 0))
			ft_strinsert_nchr(str, '0', sign, md->ex->field_width - str_len);
		else if (!(md->ex->lfjusty))
			ft_strinsert_nchr(str, ' ',
					0, md->ex->field_width - str_len);
		else
			ft_strinsert_nchr(str, ' ',
					str_len, md->ex->field_width - str_len);
	}
}
