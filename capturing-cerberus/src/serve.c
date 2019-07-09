/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:10:11 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 15:13:34 by gfielder         ###   ########.fr       */
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

void		flush_socket(int sock)
{
	char	c;

	while (recv(sock, &c, 1, 0) > 0)
		ft_putchar('.');
}

int			process_proxy_request(t_http_request *request, int client_socket)
{
	t_destination		dest;

	ft_printf("%{bright yellow}Processing Proxy Request...%{}\n\n");
	if (restructure_http_request(request) < 0)
	{
		ft_printf("%{bright red}Unexpected error 42. Sending Interface.%{}\n");
		return (send_interface(client_socket,
					"Error: Failed to restructure the HTTP Request."));
	}
	ft_printf("%{yellow}Restructured request:%{}\n\n%s", request->request);
	ft_printf("%{yellow}Target name:%{} \"%s\"\n\n", request->target_name);
	dest = resolve_target(request->target_name);
	if (!(dest.address_len))
	{
		return (send_interface(client_socket,
					"404: The requested resource was not found."));
	}
	return (proxy_http(request, dest, client_socket));
}

int			process_request(t_http_request *request, int client_socket)
{
	if (ft_strstr(request->orig_request, "Referer:"))
	{
		ft_printf("%{yellow}Referer request, sending 404%{}\n");
		return (send_404(client_socket));
	}
	if (ft_strstr(request->orig_request, "?goto=http://"))
		return (process_proxy_request(request, client_socket));
	ft_printf("%{yellow}Not a proxy request, sending interface...%{}\n");
	return (send_interface(client_socket,
				"No proxy request, or invalid input given."));
}

void		serve_request(int request_number)
{
	int					client_socket;
	int					status;
	t_http_request		request;

	ft_bzero(&request, sizeof(t_http_request));
	listen(g_server_socket, 0);
	ft_printf("%{bright yellow}Listening...%{}\n");
	client_socket = accept(g_server_socket, NULL, NULL);
	ft_printf("%{bright yellow}Connected socket %i.", client_socket);
	ft_printf(" Receiving http request...%{}\n");
	receive_http_request(client_socket, &request);
	ft_printf("%{bright yellow}Got HTTP Request:%{}\n\n%s",
			request.orig_request);
	ft_printf("%{bright yellow}Now serving request %{bright cyan}#%i%{}\n",
			request_number);
	status = process_request(&request, client_socket);
	ft_printf("\n%{bright yellow}Flushing socket...%{}\n");
	flush_socket(g_server_socket);
	ft_printf("%{bright yellow}Done.%{}\n");
	close(client_socket);
}
