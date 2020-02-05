/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:23 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/05 19:22:28 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void     parse_modifers(t_printf *p)
{
    while (1)
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

static void	parse_point(t_printf *p)
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
		p->f |= F_PRECI;
		p->f &= ~F_ZERO;
	}
    p->f &= (!p->precision && p->f & F_MINUS) ? (~F_ZERO) : 0xFFFF;
}

static void parse_flags(t_printf *p)
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

static void putchars(t_printf *p, char c, int count, t_si f_print)
{
    if (f_print)
        while (count-- > 0)
            p->done += ft_putchar(c);
}

static void print_nbr(t_printf *p, char *s, char *pref)
{
    p->width -= FT_MAX(p->precision, p->len);
    p->width -= ft_strlen(pref);
    p->precision -= p->len;
    putchars(p, ' ', !(p->f & F_ZERO) ? p->width : 0, !(p->f & F_MINUS));
	p->done += ft_putstr(pref, ft_strlen(pref));
    putchars(p, '0', (p->f & F_ZERO) ? p->width : p->precision, 1);
	p->done += ft_putstr(s, ft_strlen(s));
    putchars(p, ' ', p->width, p->f & F_MINUS);
}

static void handle_int(t_printf *p)
{
    char *str_int;
    char *pref;

    if (p->m & M_LONG || p->m & M_LONG_2)
        str_int = (p->m & M_LONG) ? ft_lltoa(va_arg(p->arg, t_l)) : ft_lltoa(va_arg(p->arg, t_ll));
    else if (p->m & M_SHORT || p->m & M_SHORT_2)
        str_int = (p->m & M_SHORT) ? ft_lltoa((t_si)va_arg(p->arg, int)) : ft_lltoa((char)va_arg(p->arg, int));
    else
        str_int = ft_lltoa(va_arg(p->arg, int));
    p->len = ft_strlen(str_int);
    pref = (*str_int == '-' && p->len--) ? "-" : 0;
    pref = (!pref && p->f & F_PLUS) ? "+" : pref;
    pref = (!pref && p->f & F_SPACE) ? " " : pref;
    print_nbr(p, str_int + (*str_int == '-'), pref);
    free(str_int);
}

static void handle_uint(t_printf *p)
{
    char *str_uint;

    if (p->m & M_LONG || p->m & M_LONG_2)
        str_uint = (p->m & M_LONG) ? ft_ulltoa_base(va_arg(p->arg, t_ul), BASE_10, 0) : ft_ulltoa_base(va_arg(p->arg, t_ull), BASE_10, 0);
    else if (p->m & M_SHORT || p->m & M_SHORT_2)
        str_uint = (p->m & M_SHORT) ? ft_ulltoa_base((t_usi)va_arg(p->arg, t_ui), BASE_10, 0) : ft_ulltoa_base((t_uc)va_arg(p->arg, t_ui), BASE_10, 0);
    else
        str_uint = ft_lltoa(va_arg(p->arg, t_ui));
    p->len = ft_strlen(str_uint);
    print_nbr(p, str_uint, 0);
    free(str_uint);
}


static void handle_hex(t_printf *p)
{
    char *str_hex;
    char *pref;

    if (p->c == 'p')
    {
    	p->m |= M_LONG_2;
        p->f &= ~(F_ZERO | F_PLUS);
    }
    if (p->m & M_LONG || p->m & M_LONG_2)
        str_hex = (p->m & M_LONG) ? ft_ulltoa_base(va_arg(p->arg, t_ul), BASE_16, p->c) : ft_ulltoa_base(va_arg(p->arg, t_ull), BASE_16, p->c);
    else if (p->m & M_SHORT || p->m & M_SHORT_2)
        str_hex = (p->m & M_SHORT) ? ft_ulltoa_base((t_usi)va_arg(p->arg, t_ui), BASE_16, p->c) : ft_ulltoa_base((t_uc)va_arg(p->arg, t_ui), BASE_16, p->c);
    else
        str_hex = ft_ulltoa_base(va_arg(p->arg, t_ui), BASE_16, p->c);
    p->f |= ('A' <= p->c && p->c <= 'Z' && p->f & F_SHARP) ? F_UPCASE : 0;
    p->len = ft_strlen(str_hex);
    pref = (p->f & F_SHARP && *str_hex != '0') ? "0x" : 0;
    pref = (pref && p->c != 'p' && p->f && p->f & F_UPCASE) ? "0X" : pref;
    print_nbr(p, str_hex, pref); 
    free(str_hex);
}

static void handle_oct(t_printf *p)
{
	char *str_oct;
    char *pref;

	if (p->m & M_LONG || p->m & M_LONG_2)
		str_oct = (p->m & M_LONG) ? ft_ulltoa_base(va_arg(p->arg, t_ul), BASE_8, p->c) : ft_ulltoa_base(va_arg(p->arg, t_ull), BASE_8, p->c);
	else if (p->m & M_SHORT || p->m & M_SHORT_2)
		str_oct = (p->m & M_SHORT) ? ft_ulltoa_base((t_usi)va_arg(p->arg, t_ui), BASE_8, p->c) : ft_ulltoa_base((t_uc)va_arg(p->arg, t_ui), BASE_8, p->c);
	else
		str_oct = ft_ulltoa_base(va_arg(p->arg, t_ui), BASE_8, p->c);
	p->len = ft_strlen(str_oct);
    pref = (p->f & F_SHARP && *str_oct != '0') ? "0" : 0;
    print_nbr(p, str_oct, pref);
	free(str_oct);
}

static void handle_char(t_printf *p)
{
	putchars(p, ' ', p->width - 1, !(p->f & F_MINUS));
	p->done += ft_putchar((t_uc)va_arg(p->arg, int));
	putchars(p, ' ', p->width - 1, p->f & F_MINUS);
}

static void handle_str(t_printf *p)
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

static void search_specifier(t_printf *p)
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
    else if (ft_strchr(PERCENT, p->c))
        print_nbr(p, 0, "%");
    // else if (ft_strchr(S_FLOAT, p->c))
    //    //     handle_float(p);
    else
        return ;
}

static void handle_specifier(t_printf *p)
{
    p->f = 0;
    p->m = 0;
    p->width = 0;
    p->precision = 0;
    parse_flags(p);
    parse_modifers(p);
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
            p->done += ft_putchar(*p->format);
        p->format++;
    }
}

int         ft_printf(const char *format, ...)
{
    t_printf p;

    ft_bzero(&p , sizeof(p));
    p.format = (char *)format;
    va_start(p.arg, format);
    parse_format(&p);
    va_end(p.arg);
    return (p.done);
}
