/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:37:12 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 21:37:48 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ls.h"

t_file		*ft_get_predecessor(t_file *f)
{
	t_file	*curr;

	if (!f)
		return (NULL);
	curr = f;
	if (f->left)
	{
		curr = f->left;
		while (curr && curr->right)
			curr = curr->right;
		return (curr);
	}
	else
	{
		while (curr && curr->parent && curr->parent->right != curr)
			curr = curr->parent;
		if (curr && curr->parent && curr->parent->right == curr)
			return (curr->parent);
		return (NULL);
	}
}

t_file		*ft_get_successor(t_file *f)
{
	t_file	*curr;

	if (!f)
		return (NULL);
	curr = f;
	if (f->right)
	{
		curr = f->right;
		while (curr && curr->left)
			curr = curr->left;
		return (curr);
	}
	else
	{
		while (curr && curr->parent && curr->parent->left != curr)
			curr = curr->parent;
		if (curr && curr->parent && curr->parent->left == curr)
			return (curr->parent);
		return (NULL);
	}
}
