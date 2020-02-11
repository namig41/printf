/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpythago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:35:55 by fpythago          #+#    #+#             */
/*   Updated: 2020/02/11 19:37:35 by fpythago         ###   ########.fr       */
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
		width = FT_MIN(len, width);
		while (i < width && vector_push_back(&p->buffer, (char *)s + i++))
			;
	}
}
