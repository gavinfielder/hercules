/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:20:05 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 20:51:43 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat_server.h"

int		cmd_help(t_server *server)
{
	char *help;

	help = get_help();
	send_message(server, server->from_user, help);
	free(help);
	return (1);
}

int		cmd_server_quit(t_server *server)
{
	(void)server;
	ft_printf("server_quit (server shutdown)\n");
	return (0);
}

int		cmd_user_quit(t_server *server)
{
	ft_printf("q (user quitting client)\n");
	broadcast_message(server, "%s has exited chat.",
			server->from_user->username);
	return (1);
}

int		cmd_change_username(t_server *server)
{
	char	*old_username;
	int		bytes;

	ft_printf("username (user changing display name)\n");
	old_username = ft_strdup(server->from_user->username);
	bytes = ft_snprintf(server->from_user->username, USERNAME_SIZE,
			"%s", server->buff + UID_LEN + 10);
	server->from_user->username[bytes] = '\0';
	broadcast_message(server, "%s is now %s.",
			old_username, server->from_user->username);
	free(old_username);
	return (1);
}

int		process_command(t_server *server)
{
	ft_printf("Command detected: ");
	if (ft_strncmp(server->buff + UID_LEN + 1, "server_quit", 11) == 0)
		return (cmd_server_quit(server));
	else if (ft_strncmp(server->buff + UID_LEN + 1, "q", 1) == 0)
		return (cmd_user_quit(server));
	else if (ft_strncmp(server->buff + UID_LEN + 1, "username", 8) == 0)
		return (cmd_change_username(server));
	else if (ft_strncmp(server->buff + UID_LEN + 1, "?", 1) == 0)
		return (cmd_help(server));
	else if (ft_strncmp(server->buff + UID_LEN + 1, "style ", 6) == 0)
		return (cmd_style(server));
	else
		ft_printf("Unknown command.\n");
	return (1);
}
