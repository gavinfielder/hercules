/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 20:33:09 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/09 14:51:28 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dgram_chat_server.h"

char	*get_help(void)
{
	t_stringbuilder *sb;
	char			*ret;

	sb = ft_sbnew();
	ft_sbprintf(sb, "%{yellow underline}DGram Chat Server: ");
	ft_sbprintf(sb, "Available Commands:%{}\n");
	ft_sbprintf(sb, "   %{bold}\\q%{}                 leaves chat.\n");
	ft_sbprintf(sb, "   %{bold}\\username %{green} name%{}    ");
	ft_sbprintf(sb, "changes username.\n");
	ft_sbprintf(sb, "   %{bold}\\style %{green}...%{}         ");
	ft_sbprintf(sb, "changes text style.\n");
	ft_sbprintf(sb, "\n");
	ft_sbprintf(sb, "  %{underline}Style options%{}: red green yellow blue ");
	ft_sbprintf(sb, "magenta cyan white black\n");
	ft_sbprintf(sb, "                 bright dim italic underline ");
	ft_sbprintf(sb, "[color]-background\n");
	ret = ft_sbtostr(sb);
	ft_sbdel(&sb);
	return (ret);
}
