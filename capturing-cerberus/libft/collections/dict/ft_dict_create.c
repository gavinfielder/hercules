/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:45:40 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/30 21:29:01 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_dict_ent		*ft_dictent_new(char *key, void *value, size_t val_size)
{
	t_dict_ent	*ent;

	if ((!key || !value || val_size == 0)
			|| (!(ent = (t_dict_ent *)malloc(sizeof(t_dict_ent)))))
		return (NULL);
	if (!(ent->value = malloc(val_size)))
		return (ft_memdelr((void **)&ent));
	if (!(ent->key = ft_strdup(key)))
	{
		ft_memdelr((void **)&(ent->value));
		return (ft_memdelr((void **)&ent));
	}
	ent->left = NULL;
	ent->right = NULL;
	ent->parent = NULL;
	ent->val_size = val_size;
	ft_memcpy(ent->value, value, val_size);
	return (ent);
}

t_dict			*ft_dict_new(int autosize)
{
	t_dict	*dict;

	if (!(dict = (t_dict *)malloc(sizeof(t_dict))))
		return (NULL);
	dict->head = NULL;
	dict->autosize = autosize;
	return (dict);
}

int				ft_dict_set(t_dict *dict, char *key, void *value, size_t size)
{
	t_dict_ent	*ent;
	void		*tmp;

	if (!dict || !key || !value)
		return (-1);
	if (dict->autosize == FTDICT_AUTO_STR)
		size = ft_strlen((char *)value) + 1;
	else if (dict->autosize)
		size = dict->autosize;
	if ((ent = ft_dict_getentry_byref(dict, key)))
	{
		if ((tmp = ft_memdup(value, size)) == NULL)
			return (-1);
		ft_memdelr(&(ent->value));
		ent->value = tmp;
		ent->val_size = size;
	}
	else
	{
		if (!(ent = ft_dictent_new(key, value, size)))
			return (-1);
		ft_dict_add(dict, ent);
	}
	return (1);
}

int				ft_dict_add(t_dict *dict, t_dict_ent *ent)
{
	t_dict_ent	**curr;
	t_dict_ent	*prev;

	if (!dict || !ent || ft_dict_getentry_byref(dict, ent->key))
		return (-1);
	if (dict->head == NULL)
		dict->head = ent;
	else
	{
		curr = ft_strcmp(ent->key, dict->head->key) < 0 ?
			&(dict->head->left) : &(dict->head->right);
		prev = dict->head;
		while (*curr != NULL)
		{
			prev = *curr;
			curr = ft_strcmp(ent->key, (*curr)->key) < 0 ?
				&((*curr)->left) : &((*curr)->right);
		}
		*curr = ent;
		ent->parent = prev;
	}
	return (0);
}
