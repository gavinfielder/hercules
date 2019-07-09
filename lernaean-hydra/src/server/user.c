/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:10:11 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 14:28:37 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat_server.h"

t_user		*add_user(t_user **head, struct sockaddr_in address,
				socklen_t addr_len, int with_id)
{
	t_user *user;
	t_user *current;

	if (head == NULL || !(user = (t_user *)malloc(sizeof(t_user))))
		return (NULL);
	ft_bzero(user, sizeof(t_user));
	user->client_address = address;
	user->client_address_len = addr_len;
	ft_strcpy(user->username, "New User");
	if (*head == NULL)
	{
		*head = user;
		user->id = 1;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = user;
		user->id = current->id + 1;
	}
	if (with_id > 0)
		user->id = with_id;
	return (user);
}

t_user		*get_user(t_user *head, int id)
{
	t_user *current;

	current = head;
	while (current && current->id != id)
		current = current->next;
	return (current);
}

int			extract_id(char *buff)
{
	char	uid_str[5];
	int		id;
	int		i;

	i = -1;
	while (++i < 4)
		uid_str[i] = buff[i];
	uid_str[4] = '\0';
	id = ft_atoi(uid_str);
	return (id);
}

void		delete_all_users(t_user **head)
{
	t_user *next;

	if (head == NULL || *head == NULL)
		return ;
	while (*head)
	{
		next = (*head)->next;
		free(*head);
		(*head) = next;
	}
}

int			replace_uid_with_username(t_user *head, char *buff, int len)
{
	t_user	*user;
	char	*tmp;

	user = get_user(head, extract_id(buff));
	ft_asprintf(&tmp, "%s: %s",
			(user == NULL ? "Anonymous" : user->username), buff + UID_LEN);
	ft_strcpy(buff, tmp);
	len += (ft_strlen(user == NULL ? "Anonymous" : user->username) - UID_LEN);
	return (len);
}
