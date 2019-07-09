/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:05:02 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 14:32:12 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat_server.h"

static int		make_echo_bot(t_server *server)
{
	sendto(server->sock, "0000I am the echo bot.", 22, 0,
			(struct sockaddr *)(&(server->server_address)),
			sizeof(server->server_address));
	return (1);
}

int				process_message(t_server *server)
{
	ft_printf("Handling Message: \"%s\"\n", server->buff);
	if (ft_strncmp(server->buff + UID_LEN, "ping", 4) == 0
			|| ft_strncmp(server->buff + UID_LEN, "\\ping", 5) == 0)
		return (pong_pong(server,
			(struct sockaddr *)(&(server->from_user->client_address)),
			server->from_user->client_address_len));
	else if (server->buff[UID_LEN] == '\\')
		return (process_command(server));
	else
		broadcast_message(server, "%s%s: %s%{}",
				server->from_user->style,
				server->from_user->username,
				server->buff + UID_LEN);
	return (1);
}

static void		determine_user(t_server *server,
					struct sockaddr_in from_address,
					socklen_t from_address_len)
{
	int		uid;

	uid = extract_id(server->buff);
	server->from_user = get_user(server->users, uid);
	if (server->from_user == NULL)
	{
		broadcast_message(server, "New User has entered chat.\n");
		server->from_user = add_user(&(server->users),
			from_address, from_address_len, uid);
		send_message(server, server->from_user,
				"**Welcome. Your ID is %04i", server->from_user->id);
		ft_printf("Setting id to %i.\n", server->from_user->id);
	}
}

void			program_loop(t_server *server)
{
	struct sockaddr_in	from_address;
	socklen_t			from_address_len;
	int					initialized;

	initialized = 0;
	while (1)
	{
		if (!(initialized))
			initialized = make_echo_bot(server);
		server->bytes_received = recvfrom(server->sock,
				server->buff, BUFF_SIZE, 0,
				(struct sockaddr *)(&from_address),
				(socklen_t *)(&from_address_len));
		if (ft_strncmp(server->buff, "ping", 4) == 0)
			pong_pong(server, (struct sockaddr *)(&from_address),
					from_address_len);
		else
		{
			determine_user(server, from_address, from_address_len);
			server->buff[server->bytes_received] = '\0';
			if (process_message(server) == 0)
				break ;
		}
	}
}

int				main(int ac, char **av)
{
	t_server	server;
	pid_t		pid;

	pid = getpid();
	if (ac > 1 && av[1][0] == '-' && ft_strchr(av[1], 'D') && daemonize(pid))
		return (0);
	server.server_address.sin_family = AF_INET;
	server.server_address.sin_port = htons(SERVER_PORT);
	server.server_address.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
	server.sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (bind(server.sock, (struct sockaddr *)(&(server.server_address)),
				sizeof(server.server_address)) < 0)
	{
		ft_printf("Bind failed with errno=%i.\n", errno);
		return (-1);
	}
	server.users = NULL;
	ft_printf("%{bright yellow}Welcome to DGram chat server.%{}\n");
	program_loop(&server);
	broadcast_message(&server, "**The server is closing now.");
	delete_all_users(&(server.users));
	close(server.sock);
	return (0);
}
