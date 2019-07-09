/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cerberus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:21:20 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 14:51:00 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CERBERUS_H
# define CERBERUS_H

# include <sys/types.h>
# include <arpa/inet.h>

# define READ_ASYNC_TIMEOUT_USEC 500000
# define READ_ASYNC_BUFFSIZE 1

typedef struct			s_http_request
{
	char				*orig_request;
	char				*request;
	char				*target_name;
}						t_http_request;

typedef struct			s_destination
{
	struct sockaddr_in	address;
	char				padding[64];
	socklen_t			address_len;
}						t_destination;

extern int				g_server_socket;
extern int				g_server_socket_proxy;
extern int				g_port;
extern int				g_port_proxy;

void					init_server_socket(void);

void					receive_http_request(int fd, t_http_request *request);
int						restructure_http_request(t_http_request *request);
int						send_interface(int fd_out, const char *error_message);
void					serve_request(int request_number);
int						send_404(int fd_out);

int						proxy_http(t_http_request *request,
							t_destination dest, int client_socket);

t_destination			resolve_target(const char *target_name);

void					timer_start(int usec);
int						timer_has_dinged(void);
void					timer_keep_going(void);

void					handle_signal_noop(int signo);

void					read_async(t_destination dest, t_stringbuilder *sb);

#endif
