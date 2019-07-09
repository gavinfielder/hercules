/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:45:40 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/30 02:11:21 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_dict_count_rec(t_dict_ent *ent)
{
	if (ent == NULL)
		return (0);
	return (1 + ft_dict_count_rec(ent->left) + ft_dict_count_rec(ent->right));
}

int				ft_dict_count_entries(t_dict *dict)
{
	if (!dict)
		return (-1);
	return (ft_dict_count_rec(dict->head));
}

void			*ft_dict_get_byref(t_dict *dict, char *key)
{
	t_dict_ent	*ent;

	if (!dict || !key)
		return (NULL);
	if (!(ent = ft_dict_getentry_byref(dict, key)))
		return (NULL);
	return (ent->value);
}

t_dict_ent		*ft_dict_getentry_byref(t_dict *dict, char *key)
{
	t_dict_ent	**curr;

	if (!dict || !key)
		return (NULL);
	curr = &(dict->head);
	while (*curr)
	{
		if (ft_strequ(key, (*curr)->key))
			return (*curr);
		else
			curr = ft_strcmp(key, (*curr)->key) < 0 ?
				&((*curr)->left) : &((*curr)->right);
	}
	return (NULL);
}
