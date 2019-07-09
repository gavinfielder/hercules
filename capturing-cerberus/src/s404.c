/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iface.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:08:49 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 14:08:51 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libft.h"
#include <netinet/tcp.h>

int			send_404(int fd_out)
{
	const char			*message = "HTTP/1.1 404 \r\n\r\n";
	int					ret;

	setsockopt(fd_out, IPPROTO_TCP, TCP_NODELAY, (void *)&fd_out, 4u);
	ret = send(fd_out, message, ft_strlen(message), 0);
	return (ret);
}
