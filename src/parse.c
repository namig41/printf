/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:23 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/08 19:04:56 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void     parse_modifiers(t_printf *p)
{
	while (ft_strchr(MODIFIERS, *p->format))
	{
		if (*p->format == 'h')
		    p->m |= (1 << (p->format[1] == 'h' && p->format++));
		else if (*p->format == 'l')
		    p->m |= (1 << (2 + (p->format[1] == 'l' && p->format++)));
		else
			return ;
		p->format++;
	}
}

inline void        parse_point(t_printf *p)
{
	if (ft_isdigit(*p->format))
	{
		p->width = ft_atoi(p->format);
		while (ft_isdigit(*p->format))
			++p->format;
	}
	if (*p->format == '.')
	{
		++p->format;
		p->precision = ft_atoi(p->format);
		while (ft_isdigit(*p->format))
			++p->format;
		p->f |= (!p->precision) ? F_PRECI : 0;
		p->f &= ~F_ZERO;
	}
    p->f &= (!p->precision && p->f & F_MINUS) ? (~F_ZERO) : 0xFFFF;
}

void        parse_flags(t_printf *p)
{
    int  n;

    while (((n = ft_strchri(FLAGS, *p->format)) > -1) && p->format++)
        p->f |= (1 << n);
	p->f &= (p->f & F_PLUS) ? (~F_SPACE) : 0xFFFF;
	if (p->f & F_WILDCARD && (p->width = va_arg(p->arg, int) < 0))
    {
            p->f |= F_MINUS;
            p->width = -p->width;
    }
}

void        search_specifier(t_printf *p)
{
    p->c = *p->format;
    if (ft_strchr(S_INT, p->c))
        handle_int(p);
    else if (ft_strchr(S_UINT, p->c))
        handle_uint(p);
    else if (ft_strchr(S_HEX, p->c))
        handle_hex(p);
    else if (ft_strchr(S_OCT, p->c))
        handle_oct(p);
    else if (ft_strchr(S_CHAR, p->c))
        handle_char(p);
    else if (ft_strchr(S_STR, p->c))
        handle_str(p);
    // else if (ft_strchr(S_FLOAT, p->c))
    //    //     handle_float(p);
    else
        return ;
}

void            handle_specifier(t_printf *p)
{
    p->f = 0;
    p->m = 0;
    p->width = 0;
    p->precision = 0;
    parse_flags(p);
    parse_modifiers(p);
    parse_flags(p);
    parse_point(p);
    search_specifier(p);
}

void            parse_format(t_printf *p)
{
    while (*p->format)
    {
        if (*p->format == '%')
        {
            p->format++;
            if (*p->format)
				handle_specifier(p);
        }
        else
        	buffer_set(p, *p->format, 1, SAVE);
        p->format++;
    }
	write(1, (char *)p->buffer.data, p->buffer.size);
}
