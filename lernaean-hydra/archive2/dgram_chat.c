/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgram_chat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:01:54 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 19:08:10 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat.h"

void strip_newlines(char *buff, int buff_size)
{
	int i;

	i = 0;
	while (i < buff_size)
	{
		if (buff[i] == '\n')
		{
			buff[i] = '\0';
			break ;
		}
		i++;
	}
}

//this function runs in the main thread and sends messages or executes commands
void program_loop(t_program_control *ctl)
{
	ssize_t chars_in_line;
	size_t line_allocation = BUFF_SIZE;
	char *line = (char *)malloc(BUFF_SIZE);
	int i;

	while (!(ctl->exit))
	{
		//get a line
		//printf("sending > ");
		chars_in_line = getline(&line, &line_allocation, stdin);
		strip_newlines(line, (int)chars_in_line);
		chars_in_line = (ssize_t)strlen(line);
		//printf("DEBUG: getline got: \"%s\"\n", line);
		i = UID_LEN;
		while (*line)
		{
			ctl->send_buff[i] = *line;
			line++;
			i++;
		}
		ctl->send_buff[i++] = '\0';
		//note i is now the size of the send_buff
		//printf("DEBUG: send_buff is now: \"%s\"\n", ctl->send_buff);

		//read the line
		if (ctl->send_buff[UID_LEN] == '\\') //is it a command?
		{
			if (ctl->send_buff[UID_LEN + 1] == 'q')
				ctl->exit = 1;
			//printf("DEBUG: exit flag has been set.\n");
		}
		//all commands and messages are sent to the server.
		//but if it's locked, wait for it to become unlocked
		while (ctl->lock_send);
		//send the message
		ctl->lock_send = 1;
		//printf("DEBUG: sending message: \"%s\"\n", ctl->send_buff);
		sendto(ctl->sock, ctl->send_buff,
				(size_t)i, 0,
				(struct sockaddr *)(&(ctl->server_address)),
				(socklen_t)sizeof(ctl->server_address));
		//printf("DEBUG: sent.\n");
		ctl->lock_send = 0;
	}
}

//this function is run asyncronously and receives messages
void *listen_for_messages(void *ctl_void)
{
	t_program_control *ctl;
	int	bytes_received;

	ctl = (t_program_control *)ctl_void;
	while (!(ctl->exit))
	{
		//printf("DEBUG: listening for message...\n");
		bytes_received = recvfrom(ctl->sock, ctl->recv_buff,
				BUFF_SIZE, 0,
				NULL, NULL);
		//printf("DEBUG: received %i bytes.\n", bytes_received);

			 	//(struct sockaddr *)(&(ctl->server_address)), don't fill
				//&(ctl->address_len)); these in or they'll be written
		//this means we're receiving from any address? hmm...
		//but maybe this is ok because the server will be sending
		//to our ip address specifically.
		
		//check for error
		if (bytes_received < 0)
		{
			printf("Error in reception thread. Closing thread now.\n");
			ctl->exit = 1;
		}
		else
		{
			//make sure we're null terminated.
			ctl->recv_buff[bytes_received] = '\0';
		}

		//see if we received an exit signal, either from the main thread
		//or from getting an error from the recvfrom function.
		if (ctl->exit)
			break ;

		//we received a message. First, see if it's a server directive.
		if (strncmp(ctl->recv_buff, "**Welcome. Your ID is ", 22) == 0)
		{
			//make sure we don't send while we write to the send buffer
			while (ctl->lock_send);
			ctl->lock_send = 1;
			strncpy(ctl->send_buff, ctl->recv_buff + 22, 4);
			ctl->lock_send = 0;
			printf("Welcome. The server has set your user id to %.4s\n", ctl->recv_buff + 22);
		}
		else if (strncmp(ctl->recv_buff, "**The server is closing now.", 28) == 0)
		{
			ctl->exit = 1;
			printf("The chat server is closing. Exiting now.\n");
			printf("Press ENTER to exit...\n");
		}
		else
		{
			//the message was not a server directive. Print the message.
			printf("%s\n", ctl->recv_buff);
		}
	}
	//printf("DEBUG: leaving listen function now...\n");
	return (NULL);
}

static void		init(t_program_control *ctl)
{
	ctl->buff_size = BUFF_SIZE - UID_LEN;
	ctl->server_address.sin_family = AF_INET;
	ctl->server_address.sin_port = htons(9005);
	ctl->server_address.sin_addr.s_addr = inet_addr("10.112.7.37");
	ctl->address_len = (socklen_t)sizeof(ctl->server_address);
	ctl->sock = socket(AF_INET, SOCK_DGRAM, 0);
	ctl->lock_send = 0;
	ctl->exit = 0;
	strncpy(ctl->send_buff, "0000", 4);
	ctl->send_buff[4] = '\0';
	printf("Welcome to dgram chat. Type \\q to quit. and \\username your_name to set your username\n");
}

int	main(void)
{
	t_program_control ctl;
	pthread_t thread_id;

	init(&ctl);
	//now split the thread to listen for messages
	pthread_create(&thread_id, NULL, listen_for_messages, (void *)(&ctl));
	//now that we're listening for messages, go into the program loop
	program_loop(&ctl);
	//we've come out of the program loop, so clean up and exit
	//just in case, let's flag ctl.exit again
	ctl.exit = 1;
	//wait for the read thread to close
	pthread_join(thread_id, NULL);
	//the read thread has exited cleanly, now close the socket
	close(ctl.sock);
	return (0);
}
