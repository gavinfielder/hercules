/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 21:46:08 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 15:26:02 by gfielder         ###   ########.fr       */
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

int		g_server_socket_proxy;
int		g_port_proxy;

void	init_server_socket_proxy(void)
{
	struct sockaddr_in	server_address;
	int					flag;

	flag = 1;
	g_server_socket_proxy = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(g_port_proxy);
	server_address.sin_addr.s_addr = inet_addr(MY_IP_ADDRESS);
	flag = 0;
	bind(g_server_socket_proxy,
			(struct sockaddr*)(&server_address),
			sizeof(server_address));
}

char	*get_response(t_destination dest)
{
	t_stringbuilder		*sb;
	char				*ret;

	sb = ft_sbnew();
	read_async(dest, sb);
	ret = ft_sbtostr(sb);
	ft_sbdel(&sb);
	return (ret);
}

int		send_response_to_client(char *response, int client_socket)
{
	int		ret;

	ret = send(client_socket, response, ft_strlen(response), 0);
	if (ret < 0)
		perror("proxy.c:77");
	free(response);
	return (ret);
}

int		proxy_http(t_http_request *request,
			t_destination dest, int client_socket)
{
	ssize_t		status;

	init_server_socket_proxy();
	if (connect(g_server_socket_proxy,
				(struct sockaddr *)&(dest.address),
				sizeof(struct sockaddr)) < 0)
	{
		ft_printf("%{bright red}Could not connect to the target.");
		ft_printf(" Sending 404.%{}\n");
		perror(NULL);
		return (send_404(client_socket));
	}
	status = sendto(g_server_socket_proxy, request->request,
			ft_strlen(request->request), 0,
			(struct sockaddr *)&(dest.address), dest.address_len);
	if (status < 0)
	{
		ft_printf("%{bright red}Error sending request to");
		ft_printf(" the target. Sending 404.%{}\n");
		perror(NULL);
		return (send_404(client_socket));
	}
	return (send_response_to_client(get_response(dest), client_socket));
}
