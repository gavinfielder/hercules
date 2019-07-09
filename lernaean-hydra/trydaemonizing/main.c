/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 12:48:11 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 13:18:56 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int	daemonize(pid_t parent)
{
	pid_t	check;
	pid_t	sid;
	int		status;

	status = fork();
	check = getpid();
	if (parent == check)
	{
		printf("this is the parent.\n");
		return (1);
	}
	else
	{
		printf("this is the child.\n");
		sid = setsid();
		if (sid < 0)
			printf("there was an error setting the session id.\n");
		if ((chdir("/")) < 0)
			printf("there was an error changing directory to root.\n");
		printf("closing stdout, stdin, and stderror now...\n");
		close(0);
		close(1);
		close(2);
		return (0);
	}
}

int	main(void)
{
	pid_t	parent;
	FILE *fout;

	printf("hello world\n");
	parent = getpid();
	if (daemonize(parent))
	{
		printf("the parent is exiting now.\n");
		return (0);
	}
	//int fd = open("hello.txt", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
	fout = fopen("hello.txt", "w");
	if (fout)
	{
		fprintf(fout, "the child was here.\n");
		fclose(fout);
	}
	else
	{
		return (-5);
	}
	return (0);
}
