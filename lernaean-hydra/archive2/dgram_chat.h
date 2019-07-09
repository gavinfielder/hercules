/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgram_chat.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:50:38 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 13:59:49 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DGRAM_CHAT_H
# define DGRAM_CHAT_H

# include <stdlib.h>
# include <stdio.h> //for printf -- delete

# include <sys/socket.h> //contains most of what we need, including the api
# include <sys/types.h>  //wasn't specified -- might be for htons()
# include <netinet/in.h> //includes structures to store address information
# include <string.h> //for strlen() -- delete
# include <unistd.h> //for close()
# include <pthread.h> 
# include <string.h>
# include <time.h>
# include <arpa/inet.h> //for inet_addr()

# define BUFF_SIZE 256
# define USERNAME_SIZE 20
# define UID_LEN 4

typedef struct		s_program_control
{
	char 			send_buff[BUFF_SIZE + 1];
	char 			recv_buff[BUFF_SIZE + 1];
	size_t			buff_size;
	struct			sockaddr_in server_address;
	socklen_t		address_len;
	int				sock;
	int				exit;
	unsigned char	lock_send;
}					t_program_control;


void				*listen_for_messages(void *ctl_void);
void				program_loop(t_program_control *ctl);

#endif
