/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 20:51:51 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 21:31:14 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat_server.h"

int		cmd_style(t_server *server)
{
	char	fmt[256];

	ft_printf("style (user-selected style)\n");
	ft_bzero(fmt, 256);
	ft_strcpy(fmt, "%{");
	ft_strcpy(fmt + 2, server->buff + UID_LEN + 7);
	ft_strcpy(fmt + ft_strlen(fmt), "}");
	ft_snprintf(server->from_user->style, 12, fmt);
	broadcast_message(server, "%s%s has changed their display style.%{}",
			server->from_user->style, server->from_user->username);
	return (1);
}
