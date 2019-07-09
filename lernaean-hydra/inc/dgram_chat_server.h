/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgram_chat_server.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:06:02 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 14:40:15 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DGRAM_CHAT_SERVER_H
# define DGRAM_CHAT_SERVER_H

# include "libft.h"
# include "libftprintf.h"
# include "ftpf_backend.h"
# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <errno.h>
# include <stdarg.h>

# define BUFF_SIZE 512
# define USERNAME_SIZE 20
# define UID_LEN 4

typedef struct			s_user
{
	int					id;
	char				username[USERNAME_SIZE + 1];
	char				style[13];
	struct s_user		*next;
	socklen_t			client_address_len;
	struct sockaddr_in	client_address;
}						t_user;

typedef struct			s_server
{
	int					sock;
	t_user				*users;
	struct sockaddr_in	server_address;
	char				buff[BUFF_SIZE + 1];
	char				send_buff[BUFF_SIZE + 1];
	int					bytes_received;
	struct sockaddr_in	from_address;
	socklen_t			from_address_len;
	t_user				*from_user;
}						t_server;

/*
** ----------------------------- User Management -------------------------------
*/

t_user					*add_user(t_user **head,
							struct sockaddr_in address,
							socklen_t addr_len, int with_id);
t_user					*get_user(t_user *head, int id);
int						extract_id(char *buff);
void					delete_all_users(t_user **head);
int						replace_uid_with_username(t_user *head,
							char *buff, int len);

/*
** ------------------------------ Transmission  --------------------------------
*/

void					broadcast_message(t_server *server,
							const char *fmt, ...);
void					send_message(t_server *server, t_user *user,
							const char *fmt, ...);

/*
** --------------------------------- General -----------------------------------
*/

void					program_loop(t_server *server);
int						process_command(t_server *server);
char					*get_help(void);
int						cmd_style(t_server *server);
int						pong_pong(t_server *server, struct sockaddr *addr,
							socklen_t len);
int						daemonize(pid_t parent);

#endif
