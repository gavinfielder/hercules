/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:06:40 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 21:03:14 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ls.h"

void				ftls_cleanup_csv(t_file *f, t_ls_options *options)
{
	(void)f;
	(void)options;
	write(1, "\x1B[2D", 4);
	write(1, "\x1B[K", 3);
	write(1, "\n", 1);
}

const static char	g_typechars[16] = {
	0, 'p', 'c', 0, 'd', 0, 'b', 0, '-', 0, 'l', 0, 's', 0, 'w', 0
};

void				ftls_outl_print_mode(t_file *f)
{
	ft_putchar(g_typechars[((f->s->st_mode & S_IFMT) >> 12) & 017]);
	ft_putchar((f->s->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((f->s->st_mode & S_IWUSR) ? 'w' : '-');
	if (f->s->st_mode & S_ISUID)
		ft_putchar((f->s->st_mode & S_IXUSR) ? 's' : 'S');
	else
		ft_putchar((f->s->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((f->s->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((f->s->st_mode & S_IWGRP) ? 'w' : '-');
	if (f->s->st_mode & S_ISGID)
		ft_putchar((f->s->st_mode & S_IXGRP) ? 's' : 'S');
	else
		ft_putchar((f->s->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((f->s->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((f->s->st_mode & S_IWOTH) ? 'w' : '-');
	if (f->s->st_mode & S_ISVTX)
		ft_putchar((f->s->st_mode & S_IXGRP) ? 't' : 'T');
	else
		ft_putchar((f->s->st_mode & S_IXGRP) ? 'x' : '-');
}

long				ftls_count_blocks(t_file *f)
{
	if (!f)
		return (0);
	return (ftls_count_blocks(f->left) + ftls_count_blocks(f->right)
			+ f->s->st_blocks);
}

struct timespec		*ftls_get_selected_timespec(t_file *f,
						t_ls_options *options)
{
	struct timespec	*ts;

	if (options->time_sel == 'm')
		ts = &(f->s->st_mtimespec);
	else if (options->time_sel == 'a')
		ts = &(f->s->st_atimespec);
	else if (options->time_sel == 'c')
		ts = &(f->s->st_ctimespec);
	else if (options->time_sel == 'U')
		ts = &(f->s->st_birthtimespec);
	else
		ts = &(f->s->st_mtimespec);
	return (ts);
}

void				ftls_set_parent_pointers(t_file *head)
{
	if (!head)
		return ;
	if (head->left)
	{
		head->left->parent = head;
		ftls_set_parent_pointers(head->left);
	}
	if (head->right)
	{
		head->right->parent = head;
		ftls_set_parent_pointers(head->right);
	}
}
