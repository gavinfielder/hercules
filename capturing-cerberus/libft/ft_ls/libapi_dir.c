/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libapi_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:45:16 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 21:38:36 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls.h"

t_file		*ft_list_directory_repl(t_file *head, const char *path,
				char *ftls_options)
{
	t_ls_options	options;

	if (head)
		ftls_del_tree(&head);
	if (!path)
		return (NULL);
	ftls_get_options(&options, (ftls_options ? ftls_options : ""));
	head = ftls_list_directory(path, &options);
	return (head);
}

t_file		*ft_list_directory(const char *path, char *ftls_options)
{
	t_ls_options	options;
	t_file			*head;

	if (!path)
		return (NULL);
	ftls_get_options(&options, (ftls_options ? ftls_options : ""));
	head = ftls_list_directory(path, &options);
	return (head);
}

t_file		*ft_match_file(t_file *head, const char *prefix)
{
	t_file	*curr;
	t_file	*tmp;

	if (!prefix)
		return (NULL);
	curr = head;
	while (curr)
	{
		if (ft_strnequ(curr->name, prefix, ft_strlen(prefix)))
		{
			tmp = ft_get_predecessor(curr);
			while (tmp)
			{
				if (ft_strnequ(tmp->name, prefix, ft_strlen(prefix)))
					curr = tmp;
				tmp = ft_get_predecessor(tmp);
			}
			return (curr);
		}
		if (ft_strcmp(prefix, curr->name) > 0)
			curr = curr->right;
		else
			curr = curr->left;
	}
	return (NULL);
}

t_file		*ft_match_file_loop(t_file *head, const char *prefix, t_file *f)
{
	t_file		*ret;

	ret = NULL;
	if (f)
	{
		ret = ft_get_successor(f);
		if (ret && !ft_strnequ(ret->name, prefix, ft_strlen(prefix)))
			ret = NULL;
	}
	if (!ret)
		ret = ft_match_file(head, prefix);
	return (ret);
}
