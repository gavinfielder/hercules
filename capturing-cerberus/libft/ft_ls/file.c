/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:30:59 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 21:04:17 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/acl.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <errno.h>
#include <sys/xattr.h>
#include "ls.h"
#include "libft.h"
#include <stdio.h>

static t_file	*fileop_abort(t_file *f)
{
	if (f)
		ftls_del_node(&f);
	perror("ft_ls");
	return (NULL);
}

static t_file	*new_file_helper(const char *path, t_file *f,
		t_ls_options *options, int tmp)
{
	if ((f->s->st_mode & S_IFMT) == S_IFLNK)
	{
		if (!(((f->link = (char *)malloc(FTLS_LINK_SIZE + 1)) == NULL) ||
				((tmp = readlink(path, f->link, FTLS_LINK_SIZE)) < 0)))
			f->link[tmp] = '\0';
		else
			perror("ft_ls");
	}
	if (options->l)
	{
		if ((tmp = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) > 0)
		{
			if ((f->xattr = (char *)malloc(tmp + 1)) &&
				(listxattr(path, f->xattr, tmp, XATTR_NOFOLLOW) > 0))
			{
				f->xattr_len = tmp;
				if (!(f->path))
					f->path = ft_strdup(path);
			}
			else
				perror("ft_ls");
		}
		f->acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	}
	return (f);
}

t_file			*ftls_new_file(const char *path, const char *filename,
					t_ls_options *options)
{
	t_file			*f;
	struct passwd	*pw;
	struct group	*gr;
	int				tmp;

	f = NULL;
	tmp = 0;
	if ((f = ftls_new_node()) == NULL)
		return (fileop_abort(f));
	ft_strncpy(f->name, filename, FTLS_NAME_SIZE);
	if (lstat(path, f->s) < 0)
		return (fileop_abort(f));
	if ((pw = getpwuid(f->s->st_uid)) != NULL)
		ft_strncpy(f->user, pw->pw_name, FTLS_USER_SIZE);
	if ((gr = getgrgid(f->s->st_gid)) != NULL)
		ft_strncpy(f->group, gr->gr_name, FTLS_GROUP_SIZE);
	if (options->p)
		f->path = ft_strdup(path);
	return (new_file_helper(path, f, options, tmp));
}

static t_file	*list_directory_helper(t_ftls_ldhelper h)
{
	if ((h.dp = opendir(h.dir)) == NULL)
		return (fileop_abort(h.head));
	while ((h.ent = readdir(h.dp)))
	{
		if (!(h.options->a) && ft_strnequ(h.ent->d_name, ".", 1))
			continue ;
		if ((h.path = ft_prepend_path(h.dir, h.ent->d_name)) == NULL)
			return (fileop_abort(NULL));
		if (!ft_strequ(h.ent->d_name, ".") && !ft_strequ(h.ent->d_name, ".."))
		{
			if ((h.f = ftls_new_file(h.path, h.ent->d_name, h.options)) == NULL)
				return (ftls_fileop_abort_close(NULL, &h));
			ftls_ins_node(&(h.head), h.f, h.options->sort, h.options->sort_dir);
			if (h.options->display_mode.note_entry)
				h.options->display_mode.note_entry(h.f, h.ent->d_namlen);
		}
		else
			ftls_ins_node(&(h.head), ftls_new_file(h.path, h.ent->d_name,
						h.options), h.options->sort, h.options->sort_dir);
		free(h.path);
	}
	closedir(h.dp);
	return (h.head);
}

t_file			*ftls_list_directory(const char *dir,
					t_ls_options *options)
{
	t_ftls_ldhelper	h;
	t_file			*ret;

	h.head = NULL;
	h.dp = NULL;
	h.ent = NULL;
	h.path = NULL;
	h.f = NULL;
	h.dir = dir;
	h.options = options;
	ret = list_directory_helper(h);
	ftls_set_parent_pointers(ret);
	return (ret);
}
