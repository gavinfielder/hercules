/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:52:58 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 14:04:52 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"
#include "libft.h"

/*
** static t_queue_ent	*ft_queue_ent_new(void *data, size_t data_size)
** {
** 	t_queue_ent		*ent;
**
** 	if (!(ent = (t_queue_ent *)ft_memalloc(sizeof(t_queue_ent))))
** 		return (NULL);
** 	ent->data = data;
** 	ent->data_size = data_size;
** 	return (ent);
** }
**
** t_queue				*ft_queue_new(int autosize)
** {
** 	t_queue		*q;
**
** 	if (!(q = (t_queue *)ft_memalloc(sizeof(t_queue))))
** 		return (NULL);
** 	q->autosize = autosize;
** 	return (q);
** }
**
** int					ft_enqueue(t_queue *q, void *data, size_t data_size)
** {
** 	t_queue_ent		*ent;
**
** 	if (!q)
** 		return (-1);
** 	if (q->autosize == FTQ_AUTO_STR)
** 		data_size = ft_strlen((char *)data);
** 	else if (q->autosize)
** 		data_size = (size_t)(q->autosize);
** 	if (!(ent = ft_queue_ent_new(data, data_size)))
** 		return (-1);
** 	if (q->tail)
** 	{
** 		q->tail->next = ent;
** 		q->tail = ent;
** 	}
** 	else
** 	{
** 		q->head = ent;
** 		q->tail = ent;
** 	}
** 	q->len++;
** 	return (1);
** }
**
** void				*ft_dequeue(t_queue *q, size_t *data_size)
** {
** 	t_queue_ent		*ent;
** 	void			*ret;
**
** 	if (!q || !(q->head))
** 		return (NULL);
** 	ent = q->head;
** 	q->head = q->head->next;
** 	if (!(q->head))
** 		q->tail = NULL;
** 	ret = ent->data;
** 	if (data_size)
** 		*data_size = ent->data_size;
** 	free(ent);
** 	q->len--;
** 	return (ret);
** }
**
** void				*ft_queue_peek(t_queue *q, size_t *data_size)
** {
** 	if (!q || !(q->head))
** 		return (NULL);
** 	if (data_size)
** 		*data_size = q->head->data_size;
** 	return (q->head->data);
** }
**
** void				ft_queue_flush(t_queue *q, int free_data_ptrs)
** {
** 	void		*tmp;
**
** 	if (!q)
** 		return ;
** 	while ((tmp = ft_dequeue(q, NULL)))
** 	{
** 		if (free_data_ptrs)
** 			free(tmp);
** 	}
** 	return ;
** }
**
** t_queue				*ft_queue_del(t_queue **q, int free_data_ptrs)
** {
** 	if (!q || !(*q))
** 		return (NULL);
** 	ft_queue_flush(*q, free_data_ptrs);
** 	free(*q);
** 	*q = NULL;
** 	return (NULL);
** }
**
** int					ft_queue_print(t_queue *q)
** {
** 	t_queue_ent		*curr;
** 	int				i;
**
** 	if (!q)
** 		return (-1);
** 	if (!(q->head))
** 		return (0);
** 	curr = q->head;
** 	i = 0;
** 	while (curr)
** 	{
** 		ft_printf("%3i: ", i);
** 		ft_putnchar_np_hex((char *)(curr->data), curr->data_size);
** 		ft_putchar('\n');
** 		curr = curr->next;
** 		i++;
** 	}
** 	return (i);
** }
*/
