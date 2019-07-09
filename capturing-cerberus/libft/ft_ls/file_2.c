/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:07:25 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 17:34:22 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ls.h"

t_file	*ftls_fileop_abort_close(t_file *f, t_ftls_ldhelper *h)
{
	if (f)
		ftls_del_node(&f);
	if (h->path)
		free(h->path);
	closedir(h->dp);
	perror("ft_ls");
	return (NULL);
}
