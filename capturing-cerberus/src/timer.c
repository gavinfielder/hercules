/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:21:51 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 15:19:22 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include "libft.h"
#include "libftprintf.h"

static pthread_t	g_timer_thread = 0;
static int			g_timer_ding = 0;
static int			g_another = 0;

void		*timer_thread(void *usec_ref)
{
	int		usec;
	int		first_time;

	usec = *((int *)usec_ref);
	first_time = 1;
	g_another = 0;
	while (first_time || g_another)
	{
		g_another = 0;
		first_time = 0;
		usleep(usec);
	}
	g_timer_ding = 1;
	ft_printf("%{red-background white}DING%{}\n");
	pthread_exit(NULL);
	return (NULL);
}

/*
** void		timer_start(int usec)
** {
** 	g_timer_ding = 0;
** 	pthread_create(&g_timer_thread, NULL, timer_thread, (void *)&usec);
** }
*/

void		timer_start(int usec)
{
	(void)usec;
	(void)g_timer_thread;
}

void		timer_keep_going(void)
{
	g_another = 1;
}

int			timer_has_dinged(void)
{
	return (g_timer_ding);
}
