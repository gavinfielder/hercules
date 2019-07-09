/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_and_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 12:28:42 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/17 14:13:30 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "../libft/inc/libft.h"
#include "../libft/inc/libftprintf.h"

int main(void)
{
	char c;
	int	bytes;
	int status;
	int server_socket;
	int client_socket;
	char *line;
	char **split;
	char *new_arg;
	char *start;
	char *destination_name;
	struct sockaddr_in server_address;
	t_stringbuilder	*request_sb;
	char	*request;

	//SOCK_STREAM is TCP, so default protocol 0 is TCP
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//set up the server address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9005);
	//server_address.sin_addr.s_addr = INADDR_ANY;
	//begin change: replacing above line
	server_address.sin_addr.s_addr = inet_addr("10.112.3.24");
	//end change
	//bind the socket to our specified IP and port
	bind(server_socket,
			(struct sockaddr*)(&server_address),
			sizeof(server_address));

	//now listen for connections
	listen(server_socket, 1);

	//got a connection(?), now accept it
	//the next args are structures that will be filled with
	//information about the client. Passing NULL ignores this behavior.
	client_socket = accept(server_socket,
			NULL, NULL);

	//Read all the data
	line = NULL;
	request_sb = ft_sbnew();
	while ((status = ft_get_next_line(client_socket, &line)) > 0)
	{
		ft_printf("Got line: ");
		ft_putnchar_np_hex(line, ft_strlen(line));
		ft_printf("\n");
		if (ft_strnequ(line, "GET ", 4))
		{
			ft_printf("Parsing GET request...\n");
			split = ft_strsplit(line, " \t\r");
			if ((start = ft_strstr(split[1], "?goto=http://")))
			{
				destination_name = ft_strdup_to_any(start + 13, "/&?\\");
				new_arg = ft_strjoin("/", start + 13 + ft_strlen(destination_name));
				ft_printf("destination_name = \"%s\"\n", destination_name);
				ft_printf("new_arg = \"%s\"\n", new_arg);
				ft_sbprintf(request_sb, "%s ", split[0]);
				ft_sbprintf(request_sb, "%s ", new_arg);
				for (int i = 2; split[i]; i++)
					ft_sbprintf(request_sb, "%s ", split[i]);
				ft_sbprintf(request_sb, "\r\n");
			}
			ft_destroy_nullterm_ptrarray((void ***)&split);
		}
		else if (ft_strequ(line, "\r"))
		{
			//End of HTTP Request
			free(line);
			break ;
		}
		else
		{
			ft_sbprintf(request_sb, "%s\n", line);
		}
		free(line);
	}
	//done with socket
	close(server_socket);
	
	request = ft_sbtostr(request_sb);
	
	ft_printf("Full request:\n\n%s\n", request);
	free(request);
	ft_sbdel(&request_sb);

	return (0);
}

















