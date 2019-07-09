/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:28:08 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 15:09:21 by gfielder         ###   ########.fr       */
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

int		g_server_socket;
int		g_port;

void	handle_signal(int signo)
{
	(void)signo;
	ft_printf("%{bright red}Closing server now.%{}\n");
	close(g_server_socket);
	close(g_server_socket_proxy);
	exit(0);
}

void	init_server_socket(void)
{
	struct sockaddr_in	server_address;
	int					flag;
	unsigned int		l;

	flag = 1;
	g_server_socket = socket(PF_INET, SOCK_STREAM, 0);
	server_address.sin_family = PF_INET;
	server_address.sin_port = htons(g_port);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	setsockopt(g_server_socket, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, 4u);
	setsockopt(g_server_socket, SOL_SOCKET, SO_REUSEADDR, (void *)&flag, 4u);
	setsockopt(g_server_socket, SOL_SOCKET, SO_REUSEPORT, (void *)&flag, 4u);
	flag = 0;
	setsockopt(g_server_socket, SOL_SOCKET, SO_KEEPALIVE, (void *)&flag, 4u);
	bind(g_server_socket,
			(struct sockaddr*)(&server_address),
			sizeof(server_address));
	getsockopt(g_server_socket, IPPROTO_TCP, SO_ERROR, (void *)&flag, &l);
	getsockopt(g_server_socket, SOL_SOCKET, SO_ERROR, (void *)&flag, &l);
}

void	get_ports(int argc, char **argv)
{
	if (argc < 3)
	{
		ft_dprintf(2, "%{bright red}Please enter two port numbers.%{}\n");
		exit(-1);
	}
	g_port = ft_atoi(argv[1]);
	g_port_proxy = ft_atoi(argv[2]);
	if (g_port < 1024 || g_port > 65535 || g_port_proxy < 1024
			|| g_port_proxy > 65535)
	{
		ft_dprintf(2, "%{bright red}Port numbers must be between 1024");
		ft_dprintf(2, " and 65535 and must be different.%{}\n");
		exit(-1);
	}
}

int		main(int argc, char **argv)
{
	int					request_number;

	get_ports(argc, argv);
	init_server_socket();
	request_number = 0;
	signal(SIGINT, handle_signal);
	signal(SIGUSR1, handle_signal_noop);
	siginterrupt(SIGUSR1, 1);
	serve_request(++request_number);
	close(g_server_socket);
}
