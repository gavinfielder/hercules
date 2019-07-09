/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:00:04 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 16:45:59 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat.h"

static void		set_username(t_program_control *ctl)
{
	ssize_t		chars_in_line;
	char		*line;

	ft_printf("%{dim cyan}Enter your username (up to %i characters)%{} > ",
			USERNAME_SIZE);
	chars_in_line = (ssize_t)ft_get_next_line(0, &line);
	send_message(ctl, "\\username %s", line);
	free(line);
}

static void		init(t_program_control *ctl)
{
	ctl->buff_size = BUFF_SIZE - UID_LEN;
	ctl->server_address.sin_family = AF_INET;
	ctl->server_address.sin_port = htons(SERVER_PORT);
	ctl->server_address.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
	ctl->address_len = sizeof(ctl->server_address);
	ctl->sock = socket(AF_INET, SOCK_DGRAM, 0);
	ctl->lock_send = 0;
	ctl->exit = 0;
	ft_strncpy(ctl->send_buff, "0000", 4);
	ctl->send_buff[4] = '\0';
	ft_printf("%{bright yellow}Welcome to DGram Chat. Type \\q to quit%{}\n");
	ft_printf("%{bright yellow}  or \\? to see a list of commands.%{}\n");
	set_username(ctl);
}

void			program_loop(t_program_control *ctl)
{
	ssize_t		chars_in_line;
	char		*line;

	line = NULL;
	while (!(ctl->exit))
	{
		chars_in_line = (ssize_t)ft_get_next_line(0, &line);
		if (line[0] == '\\' && line[1] == 'q')
			ctl->exit = 1;
		send_message(ctl, "%s", line);
		if (line)
			ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
}

int				main(void)
{
	t_program_control	ctl;
	pthread_t			thread_id;

	init(&ctl);
	pthread_create(&thread_id, NULL, listen_for_messages, (void *)(&ctl));
	program_loop(&ctl);
	ctl.exit = 1;
	pthread_join(thread_id, NULL);
	close(ctl.sock);
	return (0);
}
