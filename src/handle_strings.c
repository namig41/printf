/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
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
	putchars(p, ' ', p->width - 1, !(p->f & F_MINUS));
	p->done += ft_putchar(p->c != '%' ? (t_uc)va_arg(p->arg, int) : p->c);
	putchars(p, ' ', p->width - 1, p->f & F_MINUS);
}

void handle_str(t_printf *p)
{
	char *str;

	str = va_arg(p->arg, char *);
    if (!str)
	{
        p->done += ft_putstr(STR_NULL, sizeof(STR_NULL));
        return ;
    }
	p->len = ft_strlen(str);
	p->precision = p->precision ? FT_MIN(p->len, p->precision) : p->len;
	p->width -= p->precision;
	putchars(p, ' ', p->width, !(p->f & F_MINUS));
	p->done += ft_putstr(str, p->precision);
	putchars(p, ' ', p->width, p->f & F_MINUS);
}
