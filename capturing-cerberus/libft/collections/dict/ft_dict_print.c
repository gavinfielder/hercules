/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:58:46 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/24 20:02:10 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

int			ft_dict_print_entry(t_dict_ent *ent, int extended)
{
	char	*fmt;

	if (!ent)
		return (-ft_printf("(ent is null)\n"));
	if (extended)
		ft_asprintf(&fmt,
				"{%p :: %%s : %%#.%lum :: left=%p, right=%p, parent=%p}\n",
				ent, ent->val_size, ent->left, ent->right, ent->parent);
	else
		ft_asprintf(&fmt, "{%%s : %%#.%lum}\n", ent->val_size);
	ft_printf(fmt, ent->key, ent->value);
	free(fmt);
	return (1);
}

int			ft_dict_print_tree(t_dict_ent *ent, int extended, int depth)
{
	int		i;

	if (!ent)
		return (-ft_printf("(ent is null)\n"));
	if (ent->left)
		ft_dict_print_tree(ent->left, extended, depth + 1);
	i = 0;
	while (++i <= 4 * depth)
		ft_putchar(' ');
	ft_dict_print_entry(ent, extended);
	if (ent->right)
		ft_dict_print_tree(ent->right, extended, depth + 1);
	return (1);
}

static int	ft_dict_print_rec(t_dict_ent *ent)
{
	char	*fmt;

	ft_asprintf(&fmt, "\"%s\" => \"%%#.%lum\"\n", ent->key, ent->val_size);
	if (ent->left)
		ft_dict_print_rec(ent->left);
	ft_printf(fmt, ent->value);
	free(fmt);
	if (ent->right)
		ft_dict_print_rec(ent->right);
	return (1);
}

int			ft_dict_print(t_dict *dict)
{
	if (!dict)
		return (-ft_printf("(dict is null)\n"));
	ft_printf("dict: autosize=%i; Values:\n", dict->autosize);
	if (!(dict->head))
		return (-ft_printf("(dict is empty)\n"));
	ft_dict_print_rec(dict->head);
	return (1);
}
