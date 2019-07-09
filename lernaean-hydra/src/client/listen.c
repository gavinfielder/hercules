/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:56:15 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 17:13:15 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat.h"

static void	process_message(t_program_control *ctl)
{
	if (ft_strncmp(ctl->recv_buff, "**Welcome. Your ID is ", 22) == 0)
	{
		while (ctl->lock_send)
			;
		ctl->lock_send = 1;
		ft_strncpy(ctl->send_buff, ctl->recv_buff + 22, 4);
		ctl->lock_send = 0;
		ft_printf("%{green}Welcome. Your user id is %.4s%{}\n",
				ctl->recv_buff + 22);
	}
	else if (ft_strncmp(ctl->recv_buff,
				"**The server is closing now.", 28) == 0)
	{
		ctl->exit = 1;
		ft_printf("%{yellow}The chat server is closing. Exiting now.%{}\n");
		ft_printf("Press ENTER to exit...\n");
	}
	else
		ft_printf("%s\n", ctl->recv_buff);
}

void		*listen_for_messages(void *ctl_void)
{
	t_program_control	*ctl;
	int					bytes_received;

	ctl = (t_program_control *)ctl_void;
	while (!(ctl->exit))
	{
		bytes_received = recvfrom(ctl->sock, ctl->recv_buff,
				BUFF_SIZE, 0,
				NULL, NULL);
		if (bytes_received < 0)
		{
			ft_printf("Error in reception thread. Setting exit flag.\n");
			ctl->exit = 1;
		}
		else
			ctl->recv_buff[bytes_received] = '\0';
		if (ctl->exit)
			break ;
		process_message(ctl);
	}
	return (NULL);
}
