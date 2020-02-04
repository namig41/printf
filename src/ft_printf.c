/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:23 by lcarmelo          #+#    #+#             */
/*   Updated: 2019/11/29 22:30:41 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		//p->width = ft_max(1, ft_atoi(p->format));
		p->width = ft_atoi(p->format);
		while (ft_isdigit(*p->format))
			++p->format;
	}
	if (*p->format == '.')
	{
		++p->format;
		//p->precision = ft_max(ft_atoi(p->format), 0);
		p->precision = ft_atoi(p->format);
		while (ft_isdigit(*p->format))
			++p->format;
		p->f |= F_PRECI;
		p->f &= ~F_ZERO;
	}
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

static void putchars(t_printf *p, char c, int count, t_si ori)
{
    if (!count)
        return ;
    if (ori == ORI_LEFT && !(p->f & F_MINUS))
        while (count-- > 0)
            p->done += ft_putchar(c);
    else if (ori == ORI_RIGHT && (p->f & F_MINUS))
        while (count-- > 0)
			p->done += ft_putchar(c);
}

static t_uc save_sign(t_printf *p, char **str_int)
{
    if (**str_int == '-')
    {
        p->f &= ~F_PLUS;
        ++*str_int;
        --p->len;
        return '-';
    }
    else if (p->f & F_PLUS)
        return '+';
    else if (p->f & F_SPACE)
        return ' ';
    else
        return (0);
}

static void print_int(t_printf *p, char *str_int)
{
    t_uc sign;

    sign = save_sign(p, &str_int);
    p->width -= ft_max(p->precision, p->len);
    p->width -= (sign > 0) ? 1 : 0;
    p->precision -= p->len;
	putchars(p, ' ', !(p->f & F_ZERO) ? p->width : 0, ORI_LEFT);
	p->done += ft_putchar(sign);
	putchars(p, '0', (p->f & F_ZERO) ? p->width : p->precision, ORI_LEFT);
	//p->done += ft_putchar(!(p->f & F_ZERO || p->precision >= 0) * sign);
	p->done += ft_putstr(str_int, ft_strlen(str_int));
    putchars(p, ' ', p->width, ORI_RIGHT);
}

static void handle_int(t_printf *p)
{
    char *str_int;

    if (p->m & M_LONG || p->m & M_LONG_2)
        str_int = (p->f & M_LONG) ? ft_lltoa(va_arg(p->arg, t_l)) : ft_lltoa(va_arg(p->arg, t_ll));
    else if (p->m & M_SHORT || p->m & M_SHORT_2)
        str_int = (p->f & M_SHORT) ? ft_lltoa((t_si)va_arg(p->arg, int)) : ft_lltoa((char)va_arg(p->arg, int));
    else
        str_int = ft_lltoa(va_arg(p->arg, int));
    p->len = ft_strlen(str_int);
    print_int(p, str_int);
    free(str_int);
}

static void print_uint(t_printf *p, char *str_uint)
{
    print_int(p, str_uint);
}

static void handle_uint(t_printf *p)
{
    char *str_uint;

    if (p->m & M_LONG || p->m & M_LONG_2)
        str_uint = (p->f & M_LONG) ? ft_lltoa(va_arg(p->arg, t_ul)) : ft_lltoa(va_arg(p->arg, t_ull));
    else if (p->m & M_SHORT || p->m & M_SHORT_2)
        str_uint = (p->f & M_SHORT) ? ft_lltoa((t_usi)va_arg(p->arg, t_ui)) : ft_lltoa((t_uc)va_arg(p->arg, t_ui));
    else
        str_uint = ft_lltoa(va_arg(p->arg, t_ui));
    p->len = ft_strlen(str_uint);
    print_uint(p, str_uint);
    free(str_uint);
}

static void print_hex(t_printf *p, char *str_hex)
{
    char *pref;

    pref = 0;
    if (p->f & F_SHARP && *str_hex != '0')
    	pref = (p->f & F_UPCASE) ? "0X" : "0x";
    if (p->c == 'p')
		pref = "0x";
    p->width -= ft_max(p->precision, p->len);
    p->width -= ft_strlen(pref);
    p->precision -= p->len;
    putchars(p, ' ', !(p->f & F_ZERO) ? p->width : 0, ORI_LEFT);
	p->done += ft_putstr(pref, ft_strlen(pref));
    putchars(p, '0', (p->f & F_ZERO) ? p->width : p->precision, ORI_LEFT);
	p->done += ft_putstr(str_hex,  ft_strlen(str_hex));
    putchars(p, ' ', p->width, ORI_RIGHT);
}


static void handle_hex(t_printf *p)
{
    char *str_hex;

    if (p->c == 'p')
    {
    	p->m |= M_LONG_2;
    	p->f &= ~F_ZERO;
		p->f &= ~F_PLUS;
    }
    if (p->m & M_LONG || p->m & M_LONG_2)
        str_hex = (p->f & M_LONG) ? ft_ulltoa_base(va_arg(p->arg, t_ul), BASE_16, p->c) : ft_ulltoa_base(va_arg(p->arg, t_ull), BASE_16, p->c);
    else if (p->m & M_SHORT || p->m & M_SHORT_2)
        str_hex = (p->f & M_SHORT) ? ft_ulltoa_base((t_usi)va_arg(p->arg, t_ui), BASE_16, p->c) : ft_ulltoa_base((t_uc)va_arg(p->arg, t_ui), BASE_16, p->c);
    else
        str_hex = ft_ulltoa_base(va_arg(p->arg, t_ui), BASE_16, p->c);
    p->f |= ('A' <= p->c && p->c <= 'Z' && p->f & F_SHARP) ? F_UPCASE : 0;
    p->len = ft_strlen(str_hex);
    print_hex(p, str_hex);
    free(str_hex);
}

static void print_oct(t_printf *p, char *str_oct)
{
	char *pref;

	pref = 0;
	if (p->f & F_SHARP && *str_oct != '0')
		pref = "0";
	p->width -= ft_max(p->precision, p->len);
	p->width -= ft_strlen(pref);
	p->precision -= p->len;
	putchars(p, ' ', !(p->f & F_ZERO) ? p->width : 0, ORI_LEFT);
	p->done += ft_putstr(pref, p->width);
	putchars(p, '0', (p->f & F_ZERO) ? p->width : p->precision, ORI_LEFT);
	p->done += ft_putstr(str_oct, ft_strlen(str_oct));
	putchars(p, ' ', p->width, ORI_RIGHT);
}

static void handle_oct(t_printf *p)
{
	char *str_oct;

	if (p->m & M_LONG || p->m & M_LONG_2)
		str_oct = (p->f & M_LONG) ? ft_ulltoa_base(va_arg(p->arg, t_ul), BASE_8, p->c) : ft_ulltoa_base(va_arg(p->arg, t_ull), BASE_8, p->c);
	else if (p->m & M_SHORT || p->m & M_SHORT_2)
		str_oct = (p->f & M_SHORT) ? ft_ulltoa_base((t_usi)va_arg(p->arg, t_ui), BASE_8, p->c) : ft_ulltoa_base((t_uc)va_arg(p->arg, t_ui), BASE_8, p->c);
	else
		str_oct = ft_ulltoa_base(va_arg(p->arg, t_ui), BASE_8, p->c);
	p->len = ft_strlen(str_oct);
	print_oct(p, str_oct);
	free(str_oct);
}

static void handle_char(t_printf *p)
{
	putchars(p, ' ', p->width - 1, ORI_LEFT);
	p->done += ft_putchar((t_uc)va_arg(p->arg, int));
	putchars(p, ' ', p->width - 1, ORI_RIGHT);
}

static void handle_str(t_printf *p)
{
	char *str;

	str = va_arg(p->arg, char *);
	p->len = ft_strlen(str);
	p->precision = p->precision ? ft_min(p->len, p->precision) : p->len;
	p->width -= p->precision;
	putchars(p, ' ', p->width, ORI_LEFT);
	p->done += ft_putstr(str, p->precision);
	//write(1, str, p->precision);
	putchars(p, ' ', p->width, ORI_RIGHT);
}


static void handle_percent(t_printf *p)
{
	print_int(p, "%");
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
     	handle_percent(p);
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
