/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 02:07:01 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 07:51:05 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

int			ft_dict_set_parse(t_dict *dict, char *cmd)
{
	t_argsarr	*split;
	int			ret;

	if (!dict || !cmd)
		return (-1);
	split = ft_strsplit_args(cmd, "=", "\"\"");
	if (split->argc != 2)
	{
		ft_argsarr_del(&split);
		return (-1);
	}
	ret = ft_dict_set(dict, split->argv[0], split->argv[1],
			ft_strlen(split->argv[1]));
	ft_argsarr_del(&split);
	return (ret);
}

static int	to_ntarr_rec(char **arr, int *len, t_dict_ent *ent)
{
	int		ret;

	ret = 0;
	if (!ent)
		return (0);
	ret += to_ntarr_rec(arr, len, ent->left);
	ft_asprintf(arr + *len, "%s=%s", ent->key, ent->value);
	(*len)++;
	ret += 1 + to_ntarr_rec(arr, len, ent->right);
	return (ret);
}

char		**ft_dict_to_ntarr(t_dict *dict)
{
	int		size;
	char	**ret;

	if (!dict)
		return (NULL);
	size = ft_dict_count_entries(dict);
	ret = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	size = 0;
	to_ntarr_rec(ret, &size, dict->head);
	return (ret);
}

t_dict		*ft_ntarr_to_dict(char **arr)
{
	int		i;
	t_dict	*dict;

	if (!arr)
		return (NULL);
	if (!(dict = ft_dict_new(FTDICT_AUTO_STR)))
		return (NULL);
	i = 0;
	while (arr[i])
	{
		ft_dict_set_parse(dict, arr[i]);
		i++;
	}
	return (dict);
}
