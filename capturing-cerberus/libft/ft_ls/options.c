/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:24:54 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 17:29:17 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ls.h"
#include "libft.h"

static void		options_init(t_ls_options *options)
{
	ft_bzero(options, sizeof(t_ls_options));
	options->sort = ftls_byname;
	options->display_mode = g_ftls_display_v;
	options->sort_dir = 1;
	options->time_sel = 'm';
}

static void		parse_option_2(t_ls_options *options, char c)
{
	if (c == 'e')
		options->lacl = 1;
	else if (c == 'f')
		options->sort = ftls_nosort;
	else if (c == 'G')
		options->big_g = 1;
	else if (c == 'g')
		options->g = 1;
	else if (c == 'm')
		options->display_mode = g_ftls_display_c;
	else if (c == 'n')
		options->n = 1;
	else if (c == 'S')
		options->sort = ftls_bysize;
	else if (c == 'u')
		options->time_sel = 'a';
	else if (c == 'U')
		options->time_sel = 'U';
}

static void		parse_option_1(t_ls_options *options, char c)
{
	if (c == 'a')
		options->a = 1;
	else if (c == 'l')
	{
		options->l = 1;
		options->display_mode = g_ftls_display_l;
	}
	else if (c == 'p')
		options->p = 1;
	else if (c == 'r')
		options->sort_dir = -1;
	else if (c == 't')
		options->sort = ftls_bytime;
	else if (c == '@')
		options->lxattr = 1;
	else if (c == '1')
		options->display_mode = g_ftls_display_v;
	else if (c == 'C')
		options->display_mode = g_ftls_display_h;
	else if (c == 'c')
		options->time_sel = 'c';
	else if (c == 'd')
		options->d = 1;
	else
		parse_option_2(options, c);
}

static void		options_debrief(t_ls_options *options)
{
	if (options->sort == ftls_bytime)
	{
		if (options->time_sel == 'm')
			options->sort = ftls_bytime_m;
		else if (options->time_sel == 'a')
			options->sort = ftls_bytime_a;
		else if (options->time_sel == 'c')
			options->sort = ftls_bytime_c;
		else if (options->time_sel == 'U')
			options->sort = ftls_bytime_bigu;
		else
			options->sort = ftls_bytime_m;
	}
	if (options->display_mode.display == ftls_out_h && options->big_g)
		options->display_mode.display = ftls_out_h_color;
	if (options->l)
		ftls_out_l_set_outl_options(options);
}

t_ls_options	*ftls_get_options(t_ls_options *options, char *opt_str)
{
	int			i;

	i = 0;
	options_init(options);
	while (opt_str[i])
	{
		parse_option_1(options, opt_str[i]);
		i++;
	}
	options_debrief(options);
	return (options);
}
