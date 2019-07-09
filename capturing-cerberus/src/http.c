/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 12:28:42 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 00:50:10 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"
#include "cerberus.h"

void				receive_http_request(int fd, t_http_request *request)
{
	char				*line;
	t_stringbuilder		*request_sb;

	line = NULL;
	request_sb = ft_sbnew();
	while (!ft_strequ(line, "\r"))
	{
		if (line)
			ft_strdel(&line);
		if ((ft_get_next_line(fd, &line)) <= 0)
			break ;
		ft_sbprintf(request_sb, "%s\n", line);
	}
	ft_strdel(&line);
	request->orig_request = ft_sbtostr(request_sb);
	ft_sbdel(&request_sb);
}

int					restructure_http_request_helper(t_http_request *request)
{
	char			*start;
	unsigned int	idx;
	size_t			len;
	char			*temp;

	start = ft_strstr(request->request, "Host:");
	idx = (unsigned int)(start - request->request);
	len = (size_t)ft_strchr_idx(start, '\n') + 1;
	ft_asprintf(&temp, "Host: %s\r\n", request->target_name);
	ft_strrepl(&(request->request), idx, len, temp);
	free(temp);
	if ((start = ft_strstr(request->request, "Upgrade-Insecure-Requests: 1")))
	{
		ft_strrepl(&(request->request),
				(unsigned int)(start - request->request) + 27, 1, "0");
	}
	return (1);
}

int					restructure_http_request(t_http_request *request)
{
	char			*start;
	char			*temp;
	unsigned int	idx;
	size_t			len;

	request->request = ft_strdup(request->orig_request);
	if (!(start = ft_strstr(request->request, "GET "))
			|| !(ft_strstr(request->orig_request, "?goto=http://"))
			|| ft_strstr(request->orig_request, "Referer:"))
		return (-1);
	request->target_name = ft_getfield(start, 2, "/?&:\\\t\n\r ");
	start = ft_strstr(request->request, request->target_name)
		+ ft_strlen(request->target_name);
	temp = ft_getfield(start, 0, "\r\n");
	if (temp[0] == ' ')
		ft_strinsert_nchr(&temp, '/', 0, 1);
	idx = (unsigned int)(ft_strstr(request->request, "GET ") - request->request)
		+ 4;
	len = (size_t)ft_strchr_idx_any(request->request + idx, "\r\n");
	ft_strrepl(&(request->request), idx, len, temp);
	free(temp);
	return (restructure_http_request_helper(request));
}
