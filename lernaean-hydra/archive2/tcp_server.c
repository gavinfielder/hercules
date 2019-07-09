/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:34:04 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/06 15:53:07 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h> //contains most of what we need, including the api
#include <sys/types.h>  //wasn't specified -- might be for htons()
#include <netinet/in.h> //includes structures to store address information
#include <string.h> //for strlen()
#include <unistd.h> //for close()
//needed for the changes
#include <arpa/inet.h>

int main(void)
{
	const char server_message[256] = "Hello, Jin!";
	char temp[32];
	int	i;
	int server_socket;
	int client_socket;
	struct sockaddr_in server_address;

	//SOCK_STREAM is TCP, so default protocol 0 is TCP
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//set up the server address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	//server_address.sin_addr.s_addr = INADDR_ANY;
	//begin change: replacing above line
	server_address.sin_addr.s_addr = inet_addr("10.112.7.24");
	//end change
	//bind the socket to our specified IP and port
	bind(server_socket,
			(struct sockaddr*)(&server_address),
			sizeof(server_address));

	i = 0;
	while (i < 5)
	{
		//now listen for connections
		listen(server_socket, 1);

		//got a connection(?), now accept it
		//the next args are structures that will be filled with
		//information about the client. Passing NULL ignores this behavior.
		client_socket = accept(server_socket,
				NULL, NULL);
	
		//send a message to the client.
		send(client_socket, server_message, strlen(server_message), 0);

		i++;
	}	
	//done with server application, now close the socket
	close(server_socket);

	return (0);
}
