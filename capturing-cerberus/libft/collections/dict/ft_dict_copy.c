/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:58:32 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/30 21:06:54 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_dict_copy_rec(t_dict_ent *ent, t_dict *copy)
{
	if (!ent)
		return ;
	ft_dict_set(copy, ent->key, ent->value, ent->val_size);
	ft_dict_copy_rec(ent->left, copy);
	ft_dict_copy_rec(ent->right, copy);
}

t_dict		*ft_dict_copy(t_dict *dict)
{
	t_dict	*copy;

	if (!dict)
		return (NULL);
	if (!(copy = ft_dict_new(dict->autosize)))
		return (NULL);
	ft_dict_copy_rec(dict->head, copy);
	return (copy);
}
