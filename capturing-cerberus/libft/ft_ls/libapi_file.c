/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libapi_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:48:48 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/30 01:24:30 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls.h"

t_file		*ft_get_file(const char *path, char *ftls_options)
{
	t_ls_options	options;
	t_file			*f;
	char			*filename;

	ftls_get_options(&options, (ftls_options ? ftls_options : ""));
	filename = ft_basename(path);
	f = ftls_new_file(path, filename, &options);
	free(filename);
	return (f);
}

t_file		*ft_match_file_exact(t_file *head, const char *filename)
{
	t_file	*curr;

	if (!filename)
		return (NULL);
	curr = head;
	while (curr)
	{
		if (ft_strequ(curr->name, filename))
			return (curr);
		if (ft_strcmp(filename, curr->name) > 0)
			curr = curr->right;
		else
			curr = curr->left;
	}
	return (NULL);
}
