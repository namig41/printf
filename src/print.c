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

void print_nbr(t_printf *p, char *s, char *pref)
{
    p->width -= FT_MAX(p->precision, p->len);
    p->width -= ft_strlen(pref);
    buffer_set(p, ' ', !(p->f & F_ZERO) ? p->width : 0, !(p->f & F_MINUS));
	buffer_push_array(p, pref, ft_strlen(pref));
    buffer_set(p, '0', (p->f & F_ZERO) ? p->width : p->precision - p->len, SAVE);
    (p->f & F_PRECI && *s == '0') ? buffer_push_array(p, " ", p->width > 0) :
									buffer_push_array(p, s, ft_strlen(s));
    buffer_set(p, ' ', p->width, p->f & F_MINUS);
}
