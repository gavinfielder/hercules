/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iface.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:08:49 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 14:50:45 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include "libft.h"
#include "libftprintf.h"
#include "cerberus.h"
#include <netinet/tcp.h>

void		replace_error_message(char **response, const char *error_message)
{
	unsigned int	start;
	size_t			len;

	if (!(start = (unsigned int)(ft_strstr(*response,
				"REPLACE_ERROR_MESSAGE") - *response)))
		return ;
	len = 21;
	ft_strrepl(response, start, len, error_message);
}

int			send_interface(int fd_out, const char *error_message)
{
	t_stringbuilder		*sb;
	int					fd_in;
	int					ret;
	char				*line;
	char				*response;

	sb = ft_sbnew();
	ft_sbprintf(sb, "HTTP/1.1 200 OK\r\nConnection: Closed\r\n\r\n");
	fd_in = open("src/response.html", O_RDONLY);
	while ((ret = ft_get_next_line(fd_in, &line)) > 0)
	{
		ft_sbprintf(sb, "%s\n", line);
		free(line);
	}
	close(fd_in);
	line = ft_sbtostr(sb);
	ft_asprintf(&response, "%s%c%c", line, 4, 0);
	replace_error_message(&response, error_message);
	setsockopt(fd_out, IPPROTO_TCP, TCP_NODELAY, (void *)&fd_out, 4u);
	ret = send(fd_out, response, ft_strlen(response), 0);
	ft_sbdel(&sb);
	free(line);
	free(response);
	return (ret);
}
