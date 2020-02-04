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
       if (*p->format == 'l')
            p->m |= (1 << (p->format[1] == 'l' && p->format++));
        else if (*p->format == 'h')
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
		p->width = ft_max(1, ft_atoi(p->format));
		while (ft_isdigit(*p->format))
			++p->format;
	}
	if (*p->format == '.')
	{
		++p->format;
		p->precision = ft_max(ft_atoi(p->format), 0);
		while (ft_isdigit(*p->format))
			++p->format;
		p->f |= F_PRECI;
	}
}

static void parse_flags(t_printf *p)
{
    int  n;

    while (((n = ft_strchri(FLAGS, *p->format)) > -1) && p->format++)
        p->f |= (1 << n);
    p->f &= (p->f & F_PLUS) ? (~F_SPACE) : 1;
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
            ft_putchar(c);
    else if (ori == ORI_RIGHT && (p->f & F_MINUS))
        while (count-- > 0)
            ft_putchar(c);
}

static t_uc save_sign(t_printf *p, char **str_int)
{
    if (**str_int == '-')
    {
        p->f &= (p->f & F_PLUS) ? ~F_PLUS : 1;
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
    putchars(p, ' ', p->width, ORI_LEFT);
    ft_putchar((p->f & F_ZERO || p->precision >= 0) * sign);
    putchars(p, '0', p->precision, ORI_LEFT);
    ft_putchar(!(p->f & F_ZERO || p->precision >= 0) * sign);
    ft_putstr(str_int);
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

static void search_specifier(t_printf *p)
{
    p->c = *p->format;
    if (ft_strchr(S_INT, p->c))
        handle_int(p);
    // else if (ft_strchr(S_HEX, p->c))
    //     handle_hex(p);
    // else if (ft_strchr(S_OCT, p->c))
    //     handle_oct(p);
    // else if (ft_strchr(S_FLOAT, p->c))
    //     handle_float(p);
    // else if (ft_strchr(S_CHAR, p->c))
    //     handle_char(p);
    // else if (ft_strchr(S_STR, p->c))
    //     handle_str(p);
    // else if (ft_strchr(S_PTR, p->c))
    //     handle_ptr(p);
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
            else
                break ;
        }
        else
            ft_putchar(*p->format);
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
    return (p.done);
}
