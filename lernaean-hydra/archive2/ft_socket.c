/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:57:25 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/06 14:06:08 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_socket.h"

int make_named_socket (const char *filename)
{
	struct sockaddr_un name;
	int sock;
	size_t size;
	
	/* Create the socket. */
	sock = socket (PF_LOCAL, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror ("socket");
		exit (EXIT_FAILURE);
	}
	/* Bind a name to the socket. */
	name.sun_family = AF_LOCAL;
	strncpy (name.sun_path, filename, sizeof (name.sun_path));
	name.sun_path[sizeof (name.sun_path) - 1] = '\0';

    /* The size of the address is
       the offset of the start of the filename,
       plus its length (not including the terminating null byte).
       Alternatively you can just do:
       size = SUN_LEN (&name);
    */
	size = (offsetof (struct sockaddr_un, sun_path)
			+ strlen (name.sun_path));
	
	if (bind (sock, (struct sockaddr *) &name, size) < 0)
	{
		perror ("bind");
		exit (EXIT_FAILURE);
	}
	
	return (sock);
}
