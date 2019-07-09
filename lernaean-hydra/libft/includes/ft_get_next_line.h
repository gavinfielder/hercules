/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 22:34:35 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 14:24:52 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# define GNL_BUFF_SIZE 1
# define MIN_LEAF_SIZE 128

# define GNL_EOF 0
# define GNL_OK 1
# define GNL_ERROR -1

# define FDH_GET 0
# define FDH_RMV 1

# define MALLOC_GUARD(x) if (!(x)) return (GNL_ERROR)
# define MALLOC_GUARDN(x) if (!(x)) return (NULL)

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct			s_fdh_initializer
{
	char				nums[28];
	int					bytes;
	int					fd;
	t_hat				*hat;
	char				*check;
	int					found;
	int					total_bytes;

	struct s_fdhandler	*next;
}						t_fdh_initializer;

typedef struct			s_fdhandler
{
	int					index;
	int					line_start;
	int					bytes_to_eof;
	struct s_fdhandler	*prev;
	int					bytes;
	int					fd;
	t_hat				*hat;
	char				*check;
	int					found;
	int					total_bytes;

	struct s_fdhandler	*next;
}						t_fdhandler;

typedef union			u_fdhandler
{
	t_fdh_initializer	i;
	t_fdhandler			a;
}						t_fdhandler_u;

int						ft_get_next_line(const int fd, char **line);

#endif
