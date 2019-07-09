/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:52:33 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 16:55:33 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <unistd.h>
#include <time.h>
#include "libft.h"
#include "libftprintf.h"
#include "ls.h"

static t_ftls_outlo	g_out_l_option = NULL;

void				ftls_print_time(t_file *f, t_ls_options *options)
{
	struct timespec	*ts;
	char			*timestr;

	ts = ftls_get_selected_timespec(f, options);
	timestr = ctime(&(ts->tv_sec));
	if (options->big_t)
		write(1, timestr, 24);
	else if (time(0) - ts->tv_sec > 15552000)
	{
		write(1, timestr + 4, 7);
		write(1, timestr + 20, 4);
		write(1, " ", 1);
	}
	else
		write(1, timestr + 4, 12);
	write(1, " ", 1);
}

void				ftls_print_xattr(t_file *f)
{
	ssize_t	i;
	ssize_t	prev_ws;
	char	buff[1024];
	ssize_t	len;

	i = 0;
	prev_ws = 1;
	while (i < f->xattr_len)
	{
		if (prev_ws && f->xattr[i])
		{
			len = getxattr(f->path, f->xattr + i, buff, 1024,
					0, XATTR_NOFOLLOW);
			ft_printf("      %s: %lli\n", f->xattr + i, len);
		}
		prev_ws = (f->xattr[i] == '\0');
		i++;
	}
}

void				ftls_out_l_set_outl_options(t_ls_options *options)
{
	if (!(options->g) && !(options->n))
		g_out_l_option = ftls_out_l_n0g0;
	else if (!(options->g) && options->n)
		g_out_l_option = ftls_out_l_n1g0;
	else if (options->g && !(options->n))
		g_out_l_option = ftls_out_l_n0g1;
	else
		g_out_l_option = ftls_out_l_n1g1;
}

void				ftls_out_l(t_file *f, t_ls_options *options)
{
	char	*acl_str;

	ftls_outl_print_mode(f);
	if (f->xattr)
		ft_putchar('@');
	else
		ft_putchar(f->acl ? '+' : ' ');
	g_out_l_option(f);
	ftls_print_time(f, options);
	if (options->big_g)
		ftls_out_color(f);
	ft_putstr(f->name);
	if (options->big_g)
		ft_putstr("\x1B[0m");
	if (f->link)
		ft_printf(" -> %s", f->link);
	ft_putchar('\n');
	if (options->lxattr && f->xattr)
		ftls_print_xattr(f);
	if (options->lacl && f->acl)
	{
		acl_str = acl_to_text(f->acl, NULL);
		ft_printf(" %s\n", acl_str);
		acl_free((void *)acl_str);
	}
}

void				ftls_outl_print_totalblocks(t_file *f,
						t_ls_options *options)
{
	long	blocks;

	(void)options;
	blocks = ftls_count_blocks(f);
	ft_printf("total %li\n", blocks);
}
