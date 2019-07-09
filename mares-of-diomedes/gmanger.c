/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gmanger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 21:38:56 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/21 00:40:10 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

int tamed;
int pid;

void	not_food(int signal)
{
	printf("The horse named %i refuses to die.\n", pid);
}

void	food(int signal)
{
	if (tamed)
		printf("The tame horse named %i gladly takes additional food.\n", pid);
	tamed = 1;
}

void	die(int signal)
{
	printf("The tame horse named %i, knowing its time of magnificence has ended, joins the herd in the fields of Thrace.\n", pid);
	exit (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char const *str)
{
	if (str == NULL)
		return ;
	write(1, str, ft_strlen(str));
}

int is_prime(int num)
{
	if (num <= 1) return 0;
	if (num % 2 == 0 && num > 2) return 0;
	for(int i = 3; i < num / 2; i += 2)
	{
		if (num % i == 0)
			return 0;
	}
	return 1;
}

void	horse(void);

void	signals_untame(void)
{
	signal(SIGABRT, food);
	signal(SIGALRM, not_food);
	signal(SIGBUS, food);
	signal(SIGCHLD, not_food);
	signal(SIGCONT, not_food);
	signal(SIGFPE, food);
	signal(SIGHUP, not_food);
	signal(SIGILL, food);
	signal(SIGINT, not_food);
	signal(SIGPIPE, not_food);
	signal(SIGQUIT, food);
	signal(SIGSEGV, food);
	signal(SIGTERM, not_food);
	signal(SIGTSTP, not_food);
	signal(SIGTTIN, not_food);
	signal(SIGTTIN, not_food);
	signal(SIGTTOU, not_food);
	signal(SIGUSR1, not_food);
	signal(SIGUSR2, not_food);
	signal(SIGPROF, not_food);
	signal(SIGSYS, food);
	signal(SIGTRAP, food);
	signal(SIGURG, not_food);
	signal(SIGVTALRM, not_food);
	signal(SIGXCPU, food);
	signal(SIGXFSZ, food);
}

void	signals_tame(void)
{
	signal(SIGABRT, food);
	signal(SIGALRM, die);
	signal(SIGBUS, food);
	signal(SIGCHLD, die);
	signal(SIGCONT, die);
	signal(SIGFPE, food);
	signal(SIGHUP, die);
	signal(SIGILL, food);
	signal(SIGINT, die);
	signal(SIGPIPE, die);
	signal(SIGQUIT, food);
	signal(SIGSEGV, food);
	signal(SIGTERM, die);
	signal(SIGTSTP, die);
	signal(SIGTTIN, die);
	signal(SIGTTIN, die);
	signal(SIGTTOU, die);
	signal(SIGUSR1, die);
	signal(SIGUSR2, die);
	signal(SIGPROF, die);
	signal(SIGSYS, food);
	signal(SIGTRAP, food);
	signal(SIGURG, die);
	signal(SIGVTALRM, die);
	signal(SIGXCPU, food);
	signal(SIGXFSZ, food);
}

int		main(void)
{
	//int count = 0;
	pid = getpid();
	tamed = 0;
	while (!tamed)
	{
		if (fork() == 0)
		{
			pid = getpid();
		}
		signals_untame();
		if (is_prime(pid))
		{
			usleep(100000 * (pid % 7));
			horse();
		}
		sleep(1);
		//if (count > 100)
			//exit(0);
	}
	printf("The horse named %i has been tamed!\n", pid);
	if (is_prime(pid))
		printf("Noting in particular the magnificent beast, hercules reserves the horse named %i for Eurystheus\n", pid);
	else
	{
		printf("Having been tamed, the horse named %i calmly joins the herd in the fields of Thrace\n", pid);
		exit(0);
	}
	srand(time(0) + pid);
	while (1)
	{
		signals_tame();
		//sleep between 5 and 10 seconds
		sleep(5);
		usleep(rand() % 5000000 + 1);
		printf("A retainer of Eurystheus finds a golden egg in a field stamped with the letters \"With love from %i\"\n", pid);
	}
	return (0);
}

void	horse(void)
{
	ft_putstr("                                    /(*\n");
	ft_putstr("                                    (((,\n");
	ft_putstr("                                   ((((((.       .//,,....\n");
	ft_putstr("                                   (#((###( ./((((((((/(######*.\n");
	ft_putstr("                                   ,(####(#(#%#%%##(/(/(//****//(,.\n");
	ft_putstr("                                   .#//(#(##%##((,#//(/*//(///****,/((,\n");
	ft_putstr("                                   .#(//((####/#& %#.*//**////////****,/\n");
	ft_putstr("                                     .*/(#((((/%%*## ,/**////((/(/(////***.\n");
	ft_putstr("                                       ,/((((((/(///***//////(////(/((/(((((/**\n");
	ft_putstr("                                      .,/((/((///****///////////(((((((((((((((((////\n");
	ft_putstr("                                     .,*///////*/****/////////////((((((((((##&%&&&%(%\n");
	ft_putstr("                                     ,//////**/***/////////////((((((((((###%&(%&&&@#%%%%,\n");
	ft_putstr("                                    .,/////******///*/*////((((/((((((((((##%&%&&&@@@&/&&%#\n");
	ft_putstr("                                    .*////****/*////////////(/((((((((((((#%%(%&&&&&%*(%&%%%#,\n");
	ft_putstr("                                    ,/////**//////*//////*///(/((((((((((#%%#%%%%%%%%&%%&%%##/\n");
	ft_putstr("                                   .//////****///***/**/////**//((((((((#%%%##%%%&&&&&&&&%###%,\n");
	ft_putstr("                                   .//////////**/****///(//////(((///((##%%#//%#%#/(/(##(/,((/#.\n");
	ft_putstr("                                   ////////////***//////(((/////////((#%&&*#%%%&%%%%%&@&%###(%#\n");
	ft_putstr("                                  ,//(((/////*/**//*///(((/((((((/(/(/#%&(%&%&&&&&&&&&@&&%((/\n");
	ft_putstr("                                  ////((((((((////**///((///////(////((%#/#&@&&%%%%%%#&%.\n");
	ft_putstr("                                 //////*/((((((((//*////((((/((((((((((##(%%#  &%##((%/\n");
	ft_putstr("                                 //////////(////(((((/(((((((((((((((((((%#(%%%#. .\n");
	ft_putstr("                                /////////((//////**/(//(/((//((((((((*,,**(#%#(%%%%%%%##*\n");
	ft_putstr("                                ///////////*/*/******///////////*           (##%%%#/,*###/\n");
	ft_putstr("                               *///(((((/*************//////////              .(####(((#/\n");
	ft_putstr("                               //(((((//***********/**/*//**//**.\n");
	ft_putstr("                               */*,,,//*********************/*****,\n");
	ft_putstr("                            *****,,,,,,********************/******.,.,\n");
	ft_putstr("                         ,*,,*,,*,*,,,,,,,/**************,********/,,****,\n");
	ft_putstr("                      .,,,,,,,,*,*,,**,*,,,,,//*********,,***,,***(,,*********\n");
	ft_putstr("                    ,,,,,,*,,,**************,,,,,///,**,,***,,*,,.,,.,,,,,*,,,,.\n");
	ft_putstr("                  ,/,,,,,*****/**********,,*,,,,,,,,,,...,(,,,,*,,.,,,..,,,,,,,,\n");
	ft_putstr("                ,,,,,********/****,,,*,,,..,,,,,,.,,,,,,,,,.,*,,,,,**,,,,*,,***,.\n");
	ft_putstr("              .*,,**********,,,,,,,,,,,,,,,,,*,,,*,****,.,,,,,,,,,*,,,,,,,,*,,,,,\n");
	ft_putstr("             ,,,,**,*,**,,,,,,,,*,,,,,,*,,****,,**,*****,,,*,,,,,,,,,,...,......*\n");
	ft_putstr("            .,,.,*****,,,,,,,,,,,*******,***,*,*,,,,,,..,,..,,,,..,,,,,,..,,,,.,#.\n");
	ft_putstr("            ..,,,,,,,.,.,,,,,*,*****,***,***,.,,.,,.,,,,.,,,,,,..,.,,.,.,,,,,,,**.\n");
	ft_putstr("           ,,,,,,,.,,.,,***,*/*********,,,,,,.,,,,,,,,,,,,,,,*,,,,,,*,,,,,,,,,,(.*\n");
	ft_putstr("           ,,,**,,,,,,,,,/*,,//***,,.,,.,,,,,,,,,,,,***,,***,,,,,,*,,,,,,,,,,.,*,,\n");
	ft_putstr("          .,***,*,*****,,,**,,*,.,,,,,,,,,,,*,*,,*,*,,*,,,*,,,*,*,,,,,...,,..(%,,,.\n");
	ft_putstr("          .,*****,*********(,.,*,.,,,,*,*,,**********,**,,..,,....,...,,..,..%,,,,,\n");
	ft_putstr("          ..,,.,************%,,**,*,***,,,,**,*,,,,.,.,..,,.,,...,,,,.,,.,,,,,,..,,.\n");
	ft_putstr("          ,,,,,,,,,,,,*****,#********,,,*,*,,,,,.,,,,,,..,,.,,,,,,**,,,,,,*,,.,,,*,.\n");
	ft_putstr("          ,.,,,,,,**,,,,,.,*,&*(***,**,.,,..,,,.,,,.,,.,,,*,,********,,,,,,.,***,*,..\n");
	ft_putstr("         ,**********,,.,,,,,,/%/**,,*,,,,.,.,,,,,,*,,**,*,,,****,,,,,*,,,,,.***,,,.,,\n");
	ft_putstr("         *****************,.,,@&,,,,,,,,.,,,***,,*****,,,,,*.,,,,,,..,,,,...*,,,,.,.\n");
	ft_putstr("        ,*,********/*********(@&,.,,****,******,,*****,....,,,,,,,,,,,,.,,,,.,,,,*.\n");
	ft_putstr("       .,.,,,,,,,*******,*/***@@******,,******,,,,,,,,,..,.,.,,,,,,,,,,,,,*,,*,,\n");
	ft_putstr("      .,,,,,,,,,,,,,,,,,,,,****@********,,,,,,,,,,,*,,,,.,,,,,,***,,,,*,,*,,...,.\n");
	ft_putstr("     ..***,,,,,,,,,,,,,,,.,,*,,(***,,,,,,*,**,,,..,,***,,,*,*,,*****,,,,.,,.,,,,,\n");
	ft_putstr("      ****************,,,,,,*(*#*,,,,,,,*,,*,,,,*,*****,,,*,*,,,,,,,..,,,,,.,,,.,.\n");
	ft_putstr("    .,***********************(#(*,,,.,*****/****,******,,.,,,.,,,,,,..,.,*,**,,,,,\n");
	ft_putstr("     ,,,,,*******************(@(*******/*/******,**,,,,,.,,,,,,,*.,,,,,,******,.,,\n");
	ft_putstr("    ,,,,,,,,,,,,,,,*,,*****,,@%(/**,**/**,,*,,,,..,,,*,,.,.,,,,,****,,,,,*****,.,,.\n");
	ft_putstr("    *,*,,,,,,*,,,*,,,,,*,,,,/&%/**,,*,*,*,**,,,,,,,,,,,,,*****,,,***,,,,,,,,,,,,.,,\n");
	ft_putstr("    ..,*****,*,,*,,,**,*,,,,%%%/,,*,,*****,**,,.,*****,*,****,,,**,,,,.,,,,,.,,,,,,\n");
	ft_putstr("     ......*******//*//****&%%(/*,*//////*/*/***********,****,.,,,,,,,.,,,**,,,,,,*\n");
	ft_putstr("     ......,***,,,,,,,,,**#&%%((/*//////***/***********,,,,*,,,,,,,,,,,*,***,,,,,,*\n");
	ft_putstr("      ......***,,,,,,,,,,,#%%##(///(///*///*****,,,,,**..**,,*,.,*,***,,*,,,,,,,,,*\n");
	ft_putstr("      ......***,,,,,,,,,*,/##(//////****,***,,,,,,,**,,,.,****,**,*,*,,.,,,,,,,,,,*\n");
	ft_putstr("      .......****,,,,,,,*,,#(#((((((**,,***,,,,,,*,,*,,,,*******,**,,,...,,*,*,,,,*\n");
	ft_putstr("      .......*****,,,,,,,*,(#%%#%%%#////***,,,,****/****,******,,,,,,,..,,****,,,,*\n");
	ft_putstr("      .......**/***,,,,,,,**##%%%%%((////*/********//***,,,,,,,,,,,,,,,,,,**,**,,,*\n");
	ft_putstr("       ......*///***,,,,,,,*/#%%%%#((///**********///***.,,,*,,,,,,***,,,.,,,/*,,,*.\n");
	ft_putstr("        ......*///****,,,,,,*%#%%##(/*********,,,,,***,*.,,,,,,*,*****,,..,,,/**,,,.\n");
	ft_putstr("        .......**//******,,,,,(%###((/*,,*,,,,,**,,***,,,,************,,,..**,(/*,,,,\n");
	ft_putstr("        .......//*******,,,,,*%%%((//*****,*,,**,**/*,,,***/******,,,,,,,,**,(/**,,,\n");
	ft_putstr("         ......,//*******,,,,*%%#(##(/**//****/*/*////**,**/**,,,,,,,,,,,,,,,#(/*,**\n");
	ft_putstr("\x1B[1;33mUntame Horse is not impressed.\x1B[0;0m\n");
}

