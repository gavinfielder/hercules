/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:17:14 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 21:19:46 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat.h"

void			strip_newlines(char *buff, int buff_size)
{
	int i;

	i = 0;
	while (i < buff_size)
	{
		if (buff[i] == '\n')
		{
			buff[i] = '\0';
			break ;
		}
		i++;
	}
}

void			send_message(t_program_control *ctl, const char *fmt, ...)
{
	va_list		args;
	int			success;

	va_start(args, fmt);
	success = ft_vsnprintf(ctl->send_buff + UID_LEN,
			BUFF_SIZE - UID_LEN, fmt, args);
	va_end(args);
	while (ctl->lock_send)
		;
	ctl->lock_send = 1;
	sendto(ctl->sock, ctl->send_buff,
			(size_t)(success + UID_LEN), 0,
			(struct sockaddr *)(&(ctl->server_address)),
			sizeof(ctl->server_address));
	ctl->lock_send = 0;
}
