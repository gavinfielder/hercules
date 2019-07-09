/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 15:12:31 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 16:13:48 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

void	my_send(int sock, struct sockaddr_in *server_address, char *str)
{
	int success;

	ft_putstr("Sending: \"");
	ft_putstr(str);
	ft_putstr("\"\n");
	success = sendto(sock, str, ft_strlen(str), 0,
			(struct sockaddr *)(server_address),
			sizeof(struct sockaddr_in));
	if (success < 0)
	{
		ft_putstr("Send failed with errno=");
		ft_putnbr(errno);
		ft_putstr(".\n");
	}
}

void	my_receive(int sock)
{
	int		success;
	char	buff[512];

	ft_putstr("Waiting for server response...\n");
	success = recvfrom(sock, buff, 512, 0, NULL, NULL);
	if (success < 0)
	{
		ft_putstr("Receive failed with errno=");
		ft_putnbr(errno);
		ft_putstr(".\n");
		return ;
	}
	buff[success] = '\0';
	ft_putstr("Server response: \"");
	ft_putstr(buff);
	ft_putstr("\"\n");
}

int		main(int argc, char **argv)
{
	struct sockaddr_in	server_address;
	int					sock;

	if (argc > 1)
	{
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(SERVER_PORT);
		server_address.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock < 0)
		{
			ft_putstr("Socket failed with errno=");
			ft_putnbr(errno);
			ft_putstr(".\n");
			return (-1);
		}
		my_send(sock, &server_address, argv[1]);
		my_receive(sock);
		close(sock);
	}
	return (0);
}
