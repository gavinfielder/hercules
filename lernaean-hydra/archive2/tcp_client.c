/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:11:12 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/06 15:49:43 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h> //contains most of what we need, including the api
#include <sys/types.h>  //wasn't specified -- might be for htons()
#include <netinet/in.h> //includes structures to store address information
#include <unistd.h> // for close()
//needed for the changes
#include <arpa/inet.h>

#define BUFF_SIZE 256

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
