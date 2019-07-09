/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:58:20 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 14:58:30 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat_server.h"

/*
** This function initializes the child process
*/

static int	finish_daemonizing(void)
{
	if ((setsid()) < 0)
		ft_printf("Daemon: There was an error setting the session id.\n");
	if ((chdir("/")) < 0)
		ft_printf("Daemon: There was an error setting directory to root.\n");
	close(0);
	close(1);
	close(2);
	return (0);
}

/*
** This function will return 0 if the process is in the child, and 1 if the
** process is in the parent.
*/

int			daemonize(pid_t parent)
{
	int		status;
	pid_t	check;

	ft_printf("Daemonizing process...\n");
	status = fork();
	if (status < 0)
	{
		ft_printf("An error occurred while daemonizing. Continuing.\n");
		return (0);
	}
	check = getpid();
	if (check == parent)
	{
		ft_printf("Successfully forked. Exiting now.\n");
		return (1);
	}
	return (finish_daemonizing());
}
