/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgram_chat.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:50:38 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 14:40:52 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DGRAM_CHAT_H
# define DGRAM_CHAT_H

# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <unistd.h>
# include <pthread.h>
# include <arpa/inet.h>
# include <stdarg.h>
# include "libft.h"
# include "libftprintf.h"
# include "ftpf_backend.h"

# define BUFF_SIZE 512
# define USERNAME_SIZE 20
# define UID_LEN 4

typedef struct			s_program_control
{
	char				send_buff[BUFF_SIZE + 1];
	char				recv_buff[BUFF_SIZE + 1];
	size_t				buff_size;
	struct sockaddr_in	server_address;
	socklen_t			address_len;
	int					sock;
	int					exit;
	unsigned char		lock_send;
}						t_program_control;

void					*listen_for_messages(void *ctl_void);
void					program_loop(t_program_control *ctl);
void					strip_newlines(char *buff, int buff_size);
void					send_message(t_program_control *ctl,
							const char *fmt, ...);

#endif
