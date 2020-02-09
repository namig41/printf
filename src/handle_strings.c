/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:23 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/08 19:04:58 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void handle_char(t_printf *p)
{
	buffer_set(p, ' ', p->width - 1, !(p->f & F_MINUS));
	buffer_set(p, p->c != '%' ? (t_uc)va_arg(p->arg, int) : p->c, 1, SAVE);
	buffer_set(p, ' ', p->width - 1, p->f & F_MINUS);
}

void handle_str(t_printf *p)
{
	char *str;

	str = va_arg(p->arg, char *);
    if (!str)
	{
        buffer_push_array(p, STR_NULL, sizeof(STR_NULL));
        return ;
    }
	p->len = ft_strlen(str);
	p->precision = p->precision ? FT_MIN(p->len, p->precision) : p->len;
	p->width -= p->precision;
	buffer_set(p, ' ', p->width, !(p->f & F_MINUS));
	buffer_push_array(p, str, p->precision);
	buffer_set(p, ' ', p->width, p->f & F_MINUS);
}
