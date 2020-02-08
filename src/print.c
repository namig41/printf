/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:23 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/08 19:05:00 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline void putchars(t_printf *p, char c, int count, t_si f_print)
{
    while (f_print && count-- > 0)
        p->done += ft_putchar(c);
}

void print_nbr(t_printf *p, char *s, char *pref)
{
    p->width -= FT_MAX(p->precision, p->len);
    p->width -= ft_strlen(pref);
    putchars(p, ' ', !(p->f & F_ZERO) ? p->width : 0, !(p->f & F_MINUS));
	p->done += ft_putstr(pref, ft_strlen(pref));
    putchars(p, '0', (p->f & F_ZERO) ? p->width : p->precision - p->len, 1);
    p->done += (p->f & F_PRECI && *s == '0') ? ft_putstr(" ", p->width > 0) : ft_putstr(s, ft_strlen(s));
    putchars(p, ' ', p->width, p->f & F_MINUS);
}
