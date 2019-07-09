/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:45:40 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/24 20:29:32 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static t_dict_ent	*ft_dict_remove_twochildren(t_dict *dict, t_dict_ent *ent)
{
	t_dict_ent	*succ;

	(void)dict;
	succ = ent->right;
	while (succ->left)
		succ = succ->left;
	if (ent->parent && ent == ent->parent->right)
		ent->parent->right = succ;
	else if (ent->parent && ent == ent->parent->left)
		ent->parent->left = succ;
	if (succ != ent->right)
	{
		ent->right->parent = succ;
		succ->parent->left = NULL;
		succ->right = ent->right;
	}
	ent->left->parent = succ;
	succ->parent = ent->parent;
	succ->left = ent->left;
	return (succ);
}

static int			ft_dict_remove_entry_helper(t_dict_ent *ent,
						t_dict_ent **link)
{
	if (ent->left)
	{
		*link = ent->left;
		ent->left->parent = ent->parent;
	}
	else if (ent->right)
	{
		*link = ent->right;
		ent->right->parent = ent->parent;
	}
	else
		*link = NULL;
	return (1);
}

int					ft_dict_remove_entry(t_dict *dict, t_dict_ent *ent)
{
	t_dict_ent	**link;
	t_dict_ent	*tmp;

	if (!dict || !ent)
		return (-1);
	if (ent->left && ent->right)
	{
		tmp = ft_dict_remove_twochildren(dict, ent);
		if (ent == dict->head)
			dict->head = tmp;
		return (1);
	}
	if (ent == dict->head)
		link = &(dict->head);
	else
		link = (ent == ent->parent->left)
			? &(ent->parent->left) : &(ent->parent->right);
	return (ft_dict_remove_entry_helper(ent, link));
}

int					ft_dict_unset(t_dict *dict, char *key)
{
	t_dict_ent	*ent;
	int			status;

	status = 0;
	if (!dict || !key)
		return (-1);
	ent = ft_dict_getentry_byref(dict, key);
	if (ent)
	{
		status |= ft_dict_remove_entry(dict, ent);
		status |= ft_dictent_del(&ent);
		return (status);
	}
	return (-1);
}
