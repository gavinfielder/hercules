/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:58:25 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/06 08:12:07 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_words(const char *str, const char *delim, char *groupers)
{
	int		i;
	int		count;
	int		idx;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(delim, str[i]))
			i++;
		idx = ft_strchr_idx(groupers, str[i]);
		if (str[i] && idx >= 0 && ((idx & 1) == 0))
		{
			count++;
			while (str[++i] && (str[i] != groupers[idx + 1] || !(i++)))
				;
		}
		else if (str[i])
		{
			count++;
			while (str[i] && !ft_strchr(delim, str[i]))
				i++;
		}
	}
	return (count);
}

static void	strsplit_fill(char **ret, char const *str,
	const char *delim, char *groupers)
{
	int		i;
	int		j;
	int		idx;

	i = 0;
	j = -1;
	while (str[i])
	{
		while (str[i] && ft_strchr(delim, str[i]))
			i++;
		idx = ft_strchr_idx(groupers, str[i]);
		if (str[i] && idx >= 0 && ((idx & 1) == 0))
		{
			ret[++j] = ft_strdup_to(str + (++i), groupers[idx + 1]);
			i += ft_strlen(ret[j]);
			if (str[i] == groupers[idx + 1])
				i++;
		}
		else if (str[i])
		{
			ret[++j] = ft_strdup_to_any(str + i, delim);
			i += ft_strlen(ret[j]);
		}
	}
}

char		**ft_strsplit_grouping(char const *s,
				const char *delim, char *groupers)
{
	char	**ret;
	int		word_count;

	if (!s || !groupers)
		return (NULL);
	word_count = count_words(s, delim, groupers);
	ret = (char **)malloc(sizeof(char *) * (word_count + 1));
	strsplit_fill(ret, s, delim, groupers);
	ret[word_count] = NULL;
	return (ret);
}

char		**ft_strsplit(char const *s, const char *delim)
{
	return (ft_strsplit_grouping(s, delim, ""));
}
