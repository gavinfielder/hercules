/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgram_chat_server.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:10:50 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 17:12:32 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h> //contains most of what we need, including the api
#include <sys/types.h>  //wasn't specified -- might be for htons()
#include <netinet/in.h> //includes structures to store address information
#include <string.h> //for strlen()
#include <unistd.h> //for close()
#include <arpa/inet.h> //for inet_addr()

#define BUFF_SIZE 256
#define USERNAME_SIZE 20
#define UID_LEN 4

typedef struct s_user
{
	int id;
	struct sockaddr_in client_address;
	char username[USERNAME_SIZE + 1];
	struct s_user *next;
} t_user;

//adds a user to the list of users
t_user *add_user(t_user **head, struct sockaddr_in address, int with_id)
{
	t_user *user;
	t_user *current;

	if (head == NULL)
		return (NULL);
	user = (t_user *)malloc(sizeof(t_user));
	if (user == NULL)
		return (NULL);
	user->next = NULL;
	user->client_address = address;
	strcpy(user->username, "Anonymous");
	if (*head == NULL)
	{
		*head = user;
		user->id = 1;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		//current is the now the last node in the list
		current->next = user;
		user->id = current->id + 1;
	}
	if (with_id > 0)
		user->id = with_id;
	return (user);
}

//retrieves a user from the list of users, or else NULL if not found
t_user *get_user(t_user *head, int id)
{
	t_user *current;

	current = head;
	while (current && current->id != id)
		current = current->next;
	return (current);
}

//gets the user id out of the first part of the message
int extract_id(char *buff)
{
	char uid_str[5];
	int	id;

	for (int i = 0; i < 4; i++)
		uid_str[i] = buff[i];
	uid_str[4] = '\0';
	id = atoi(uid_str);
	return (id);
}

//deletes all users
void delete_all_users(t_user **head)
{
	t_user *next;

	if (head == NULL || *head == NULL)
		return ;
	while (*head)
	{
		next = (*head)->next;
		free(*head);
		(*head) = next;
	}
}

//shifts a message over to write over the uid portion with the user's username
int replace_uid_with_username(t_user *head, char *buff, int len)
{
	t_user *user;
	char username[USERNAME_SIZE + 1];
	int username_len;
	char temp[BUFF_SIZE + 1];
	int i, j;
	char uid_str[5];
	int	id;

	//get the username
	id = extract_id(buff);
	user = get_user(head, id);
	if (user == NULL)
		strcpy(username, "Anonymous");
	else
		strcpy(username, user->username);
	username_len = strlen(username);

	//write the username
	i = 0;
	while (i < username_len)
	{
		temp[i] = username[i];
		i++;
	}
	//write the seperator
	temp[i++] = ':';
	temp[i++] = ' ';
	//write the message
	j = UID_LEN;
	while (buff[j])
	{
		temp[i] = buff[j];
		i++;
		j++;
	}
	temp[i] = '\0';

	//now that the message is fully formed, strcpy the temp into the buff
	strcpy(buff, temp);

	len += (username_len - 4);
	return (len);
}

void broadcast_message(int sock, t_user *head, char *buff,
		int len, int with_username)
{
	t_user *current;
	ssize_t sent_bytes;

	if (buff == NULL)
		return ;
	if (with_username)
		len = replace_uid_with_username(head, buff, len);
	current = head;
	while (current)
	{
		//printf("   broadcasting to user %i... ", current->id);
		sent_bytes = sendto(sock, buff, strlen(buff), 0,
				((struct sockaddr *)(&(current->client_address))),
				sizeof(current->client_address));
		//printf("sent.\n");
		if (sent_bytes < 0)
			printf("Error sending packet: \"%s\"", buff);
		current = current->next;
	}
}

//listens for messages
void program_loop(void)
{
	char	buff[BUFF_SIZE + 1];
	char	temp[BUFF_SIZE];
	char	old_username[USERNAME_SIZE + 1];
	int		bytes_received;
	int		server_socket;
	t_user	*users;
	t_user	*user;
	struct sockaddr_in	from_address;
	struct sockaddr_in	server_address;
	socklen_t from_address_len;
	int		quit;
	char	uid_str[UID_LEN + 1];
	int		uid;
	int		new_user_id;

	//printf("DEBUG: Initializing... ");

	//from_address is apparently filled in, so do we need this? I don't think so
	from_address.sin_family = AF_INET;
	from_address.sin_port = htons(9002);
	from_address.sin_addr.s_addr = inet_addr("10.112.7.37");

	//set up the server
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("10.112.7.37");
	server_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (bind(server_socket,
				(struct sockaddr *)(&server_address),
				sizeof(server_address)) < 0)
	{
		printf("DEBUG: bind failed.\n");
		return ;
	}
	quit = 0;
	users = NULL;

	//printf("Done.\n");
	while (!quit)
	{
		//receive a message from any source
		//printf("Listening for message now...\n");
		bytes_received = recvfrom(server_socket, buff, BUFF_SIZE, 0,
				(struct sockaddr *)(&from_address),
				(socklen_t *)(&from_address_len));
		//printf("Received %i bytes.\n", bytes_received);

		new_user_id = 0;
		//first of all, is the message from an existing user?
		uid = extract_id(buff);
		user = get_user(users, uid);
		if (user == NULL)
		{
			printf("New user. ");
			user = add_user(&users, from_address, uid);
			snprintf(temp, 27, "**Welcome. Your ID is %04i", user->id);
			temp[27] = '\0';
			printf("Setting id to %i.\n", user->id);
			//send the first-time user their user id
			//printf("Sending the user ID to the user; message=\"%s\" ... ", temp);
			printf("IP address is %s\n", inet_ntoa(user->client_address.sin_addr));
			sendto(server_socket, temp, 26, 0,
					(struct sockaddr *)(&from_address),
					(socklen_t)(from_address_len));
			//printf("Sent.\n");
			new_user_id = user->id;
		}
		//next, let's null terminate the message, just in case
		buff[bytes_received] = '\0';

		printf("Handling Message: \"%s\"\n", buff);

		//is the message a command?
		if (buff[UID_LEN] == '\\')
		{
			printf("Command detected: ");
			//figure out what the command is
			if (strncmp(buff + UID_LEN + 1, "server_quit", 11) == 0)
			{
				quit = 1;
				printf("server_quit (server shutdown)\n");
			}
			else if (strncmp(buff + UID_LEN + 1, "q", 1) == 0)
			{
				printf("q (user quitting client)\n");
				uid = extract_id(buff);
				user = get_user(users, uid);
				if (user != NULL)
					sprintf(temp, "%s has exited chat.", user->username);
				else
					sprintf(temp, "Anonymous has exited chat.");
				broadcast_message(server_socket, users,
						temp, strlen(temp), 0);
			}
			else if (strncmp(buff + UID_LEN + 1, "username", 8) == 0)
			{
				printf("username (user changing display name)\n");
				if (new_user_id)
					uid = new_user_id;
				else
					uid = extract_id(buff);
				user = get_user(users, uid);
				if (user != NULL)
				{
					strcpy(old_username, user->username);
					snprintf(user->username, USERNAME_SIZE, "%s", buff + UID_LEN + 10);
					snprintf(temp, BUFF_SIZE, "%s has set their username to %s.",
							old_username, user->username);
					broadcast_message(server_socket, users,
							temp, strlen(temp), 0);
				}
			}
			else
				printf("Unknown command.\n");
		}
		else
		{
			//we received a general message. Broadcast it to all users
			broadcast_message(server_socket, users, buff, bytes_received, 1);
		}
	}
	//exiting the program. Time to clean up. First, broadcast that the
	//server is closing. This will tell clients to exit.
	broadcast_message(server_socket, users,
			"**The server is closing now.", 28, 0);
	//now delete all users, freeing the memory they used
	delete_all_users(&users);
	//now close the socket
	close(server_socket);
}

int main(void)
{
	printf("Welcome to dgram chat server.\n");
	program_loop();
	return (0);
}


