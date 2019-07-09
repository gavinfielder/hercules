/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy_async.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 23:21:29 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 00:25:09 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "libft.h"
#include "libftprintf.h"
#include "cerberus.h"
#include <netinet/tcp.h>
#include <pthread.h>

static pthread_t		g_read_thread = 0;
static t_destination	g_dest;
static int				g_done_reading = 0;

void		*read_thread(void *sb_void)
{
	t_stringbuilder	*sb;
	char			buff[READ_ASYNC_BUFFSIZE];

	ft_bzero(buff, READ_ASYNC_BUFFSIZE);
	sb = (t_stringbuilder *)sb_void;
	while (!timer_has_dinged() && recvfrom(g_server_socket_proxy,
			buff, READ_ASYNC_BUFFSIZE, 0,
			(struct sockaddr *)&(g_dest.address), &(g_dest.address_len)) > 0)
	{
		timer_keep_going();
		ft_sbwriten(sb, buff, READ_ASYNC_BUFFSIZE);
		ft_bzero(buff, READ_ASYNC_BUFFSIZE);
		ft_putchar('`');
	}
	ft_printf("%{blue magenta-background}Completed read thread.%{}\n");
	g_done_reading = 1;
	return (NULL);
}

void		read_async(t_destination dest, t_stringbuilder *sb)
{
	int		ding;

	ding = 0;
	g_dest = dest;
	g_done_reading = 0;
	timer_start(READ_ASYNC_TIMEOUT_USEC);
	ft_printf("%{bright green}Starting asynchronous read.%{}\n");
	pthread_create(&g_read_thread, NULL, read_thread, (void *)sb);
	while (!((ding = timer_has_dinged()) || g_done_reading))
	{
		usleep(117);
	}
	if (ding)
	{
		pthread_kill(g_read_thread, SIGUSR1);
		ft_printf("%{bright green}Timed out. Stopping read.%{}\n");
	}
	else
	{
		ft_printf("%{bright green}Reading complete.%{}\n");
	}
}
