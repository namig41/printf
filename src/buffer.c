/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpythago <fpythago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:23 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/17 18:38:49 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		buffer_set(t_printf *p, char c, int count, t_uc f_save)
{
	while (f_save && count-- > 0 && vector_push_back(&p->buffer, &c))
		;
}

void		buffer_push_array(t_printf *p, const char *s, size_t width)
{
	size_t	i;
	size_t	len;

	if (s)
	{
		i = 0;
		len = ft_strlen(s);
		width = ft_min(len, width);
		while (i < width && vector_push_back(&p->buffer, (char *)s + i++))
			;
	}
}
