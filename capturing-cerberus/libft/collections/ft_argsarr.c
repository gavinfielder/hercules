/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argsarr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:57:20 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 07:50:34 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_argsarr		*ft_strsplit_args(char const *s, const char *delim,
					char *groupers)
{
	t_argsarr		*args;

	if (!s)
		return (NULL);
	if ((args = (t_argsarr *)malloc(sizeof(t_argsarr))) == NULL)
		return (NULL);
	ft_bzero(args, sizeof(t_argsarr));
	if ((args->argv = ft_strsplit_grouping(s, delim, groupers)) == NULL)
		return (ft_argsarr_del(&args));
	while (args->argv[args->argc] != NULL)
		(args->argc)++;
	return (args);
}

t_argsarr		*ft_argsarr_del(t_argsarr **args)
{
	if (!args || !(*args))
		return (NULL);
	ft_destroy_nullterm_ptrarray((void ***)&((*args)->argv));
	free(*args);
	*args = NULL;
	return (NULL);
}
