/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:45:40 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/24 20:37:09 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int					ft_dictent_del(t_dict_ent **ent)
{
	if (!ent || !(*ent))
		return (-1);
	if ((*ent)->key)
		free((*ent)->key);
	if ((*ent)->value)
		free((*ent)->value);
	ft_bzero((*ent), sizeof(t_dict_ent));
	free(*ent);
	*ent = NULL;
	return (1);
}

static void			ft_dict_del_tree(t_dict_ent **ent)
{
	if (!ent || !(*ent))
		return ;
	ft_dict_del_tree(&((*ent)->left));
	ft_dict_del_tree(&((*ent)->right));
	ft_dictent_del(ent);
}

int					ft_dict_del(t_dict **dict)
{
	if (!dict || !(*dict))
		return (-1);
	ft_dict_del_tree(&((*dict)->head));
	free(*dict);
	*dict = NULL;
	return (1);
}
