/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:52:15 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 16:02:38 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

long		ftls_byname(t_file *a, t_file *b)
{
	return (ft_strcmp(a->name, b->name));
}

long		ftls_nosort(t_file *a, t_file *b)
{
	(void)a;
	(void)b;
	return (0);
}

long		ftls_bysize(t_file *a, t_file *b)
{
	return (b->s->st_size - a->s->st_size);
}

long		ftls_bytime(t_file *a, t_file *b)
{
	(void)a;
	(void)b;
	return (0);
}
