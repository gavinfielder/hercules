/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:02:36 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 17:28:03 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

const t_ftls_display_mode	g_ftls_display_h = {
	ftls_out_h,
	ftls_begin_column_output,
	ftls_end_column_output,
	ftls_note_entry
};

const t_ftls_display_mode	g_ftls_display_v = {
	ftls_out_v,
	ftls_noop,
	ftls_noop,
	NULL
};

const t_ftls_display_mode	g_ftls_display_c = {
	ftls_out_c,
	ftls_noop,
	ftls_cleanup_csv,
	NULL
};

const t_ftls_display_mode	g_ftls_display_l = {
	ftls_out_l,
	ftls_outl_print_totalblocks,
	ftls_noop,
	NULL
};

void						ftls_out_main(t_file *head,
								t_ls_options *options)
{
	if (!head)
		return ;
	if (head->left)
		ftls_out_main(head->left, options);
	options->display_mode.display(head, options);
	if (head->right)
		ftls_out_main(head->right, options);
}

void						ftls_out_color(t_file *f)
{
	if ((f->s->st_mode & S_IFMT) == S_IFDIR)
		ft_putstr("\x1B[34m");
	else if ((f->s->st_mode & S_IFMT) != S_IFREG)
		ft_putstr("\x1B[36m");
	else if (f->s->st_mode & S_IXUSR)
		ft_putstr("\x1B[31m");
}

void						ftls_out_v(t_file *f, t_ls_options *options)
{
	(void)options;
	if (options->big_g)
		ftls_out_color(f);
	ft_putstr(f->name);
	if (options->big_g)
		ft_putstr("\x1B[0m");
	ft_putchar('\n');
}

void						ftls_out_c(t_file *f, t_ls_options *options)
{
	(void)options;
	ft_putstr(f->name);
	ft_putstr(", ");
}
