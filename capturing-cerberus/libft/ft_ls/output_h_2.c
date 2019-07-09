/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_h_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 04:14:51 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/23 17:33:34 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ls.h"

void	ftls_out_h_color(t_file *f, t_ls_options *options)
{
	(void)options;
	ftls_outh_new_entry();
	ftls_out_color(f);
	ft_putstr(f->name);
	ft_putstr("\x1B[0m");
}
