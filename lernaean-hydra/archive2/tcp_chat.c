/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_chat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:55:39 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/06 17:27:47 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>  //wasn't specified -- might be for htons()
#include <netinet/in.h> //includes structures to store address information
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h> 
#include <string.h>
#include <time.h>

#define BUFF_SIZE 512
#define TIMER_MICROSECONDS 20000 //20 milliseconds, or 0.020 of a second

typedef struct s_program_control
{
	int	sock;
	int exit;
} t_program_control;

void connect_to_server(t_program_control *ctl)
{
	char server_response[BUFF_SIZE + 1];
	int bytes_received;
	int connection_status;

	ctl->sock = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address to connect to
	struct socckaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("10.112.7.24");
	connection_status = connect(ctl->sock,




}

int main(void)
{
	int	network_socket;
	char server_response[BUFF_SIZE + 1];
	int 	bytes_received;

	//0 for protocol is default, which for SOCK_STREAM is TCP
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address to connect to
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	//server_address.sin_addr.s_addr = INADDR_ANY; //shortcut for 0.0.0.0 (me)
	//begin change: replacing above line
	server_address.sin_addr.s_addr = inet_addr("10.112.7.24");
	//end change
	int connection_status = connect(network_socket,
			(struct sockaddr *)(&server_address),
			sizeof(server_address));
	if (connection_status == -1)
	{
		printf("There was an errror making a connection the remote socket\n\n");
	}
	else
	{
		//here BUFF_SIZE is the amount of data to try to receive,
		//not the capacity of the buffer.
		//the zero at the end is for flags, which is 0 for no flags
		bytes_received = recv(network_socket, server_response, BUFF_SIZE, 0);
		server_response[bytes_received] = '\0';
		//print out the server's response
		printf("server returned %3i bytes: \"%s\"\n",
				bytes_received, server_response);
		//wait some time in order to flush the socket.
		sleep(1);
		//close the socket
		close(network_socket);
	}
	return (0);
}


//this function runs in the main thread and sends messages or executes commands
void program_loop(t_program_control *ctl)
{
	char cmd[BUFF_SIZE];
	size_t cmd_len;

	while (!(ctl->exit))
	{
		printf(" > ");
		getline(&cmd, &cmd_len, stdin);
		i = 0;
		while (i <= cmd_len && i < BUFF_SIZE)
		{
			if (cmd[i] == '\n')
			{
				cmd[i] = '\0';
				break ;
			}
			i++;
		}
		//read the command
		if (cmd[0] == '\\')
		{
			if (cmd[1] == 'q')
				ctl->exit = 1;
		}
		else
		{
			//send a message

		}
	}
}

//this function is run asyncronously and receives messages
//it may be interrupted with pthread_kill (I should find a better way)
void *listen_for_messages(void *vargp)
{
	

	return (NULL);
}

void *timer(void *dinger_int)
{
	//wait for the timer to finish
	usleep(TIMER_MICROSECONDS);
	//set the finished flag that was passed in
	*((int *)(dinger_int)) = 1;
}

int main(void)
{
	size_t username_len;
	char username[64];
	int i;

	printf("Welcome to e1z2r7p24 chat. Please enter your screen name: \n");
	getline(&username, &username_len, stdin);
	i = 0;
	while (i <= username_len && i < 64)
	{
		if (username[i] == '\n') username[i] = '\0';
		i++;
	}
	username_len = strlen(username);
	printf("You are registered as; %s\nMaking connection to server now...", username);
	//next we need to connect to the server.
	//TODO
	//Now we need to split the threads
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, listen_for_messages, NULL);
	//ok, now that we're listening for messages, go into the program loop
	
	







void *myThreadFun(void *vargp) 
{ 
    sleep(1); 
    printf("Printing GeeksQuiz from Thread \n"); 
    return NULL; 
} 
   
int main() 
{ 
    pthread_t thread_id; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, myThreadFun, NULL); 
    pthread_join(thread_id, NULL); 
    printf("After Thread\n"); 
    exit(0); 
}



