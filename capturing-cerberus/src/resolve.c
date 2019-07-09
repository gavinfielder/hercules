/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:12:15 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/18 15:12:20 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netdb.h>
#include <stdlib.h>
#include "libft.h"
#include "cerberus.h"

t_destination	resolve_target(const char *target_name)
{
	t_destination	dest;
	struct hostent	*ent;

	ft_bzero(&dest, sizeof(t_destination));
	ent = gethostbyname(target_name);
	if (!ent || ent->h_addr_list[0] == NULL)
		return (dest);
	ft_memcpy(&(dest.address.sin_addr.s_addr),
			ent->h_addr, (size_t)(ent->h_length));
	ft_memcpy(&(dest.address_len), &(ent->h_length), sizeof(socklen_t));
	dest.address.sin_port = htons(80);
	dest.address.sin_family = AF_INET;
	return (dest);
}
