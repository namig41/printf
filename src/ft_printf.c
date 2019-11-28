/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:23 by lcarmelo          #+#    #+#             */
/*   Updated: 2019/11/21 13:49:24 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int  print_int(char c, va_list arg)
{
    if (c == 'd' || c == 'i')
        ft_putnbr(va_arg(arg, int));
    else if (c == 'u')
        ft_putstr(ft_lltoa(va_arg(arg, t_ui)));
    else if (c == 'o')
       ft_putstr(ft_uitoa_base(va_arg(arg, int), 8, 'o'));
    else if (c == 'x')
        ft_putstr(ft_uitoa_base(va_arg(arg, int), 16, 'x'));
    else if (c == 'X')
         ft_putstr(ft_uitoa_base(va_arg(arg, int), 16, 'X'));
    else
        return (0);
    return (1);
}

static int  belongs_set(char c, char *s)
{
    int     len;

    len = ft_strlen(s);
    while (--len >= 0)
        if (c == s[len])
            return (1);
    return (0);
}

static void  print_float(double real)
{
    int byte;

    byte = -1;
    if (!flags.accuracy)
        flags.accuracy = 6;
    ft_putnbr((t_ui)real);
    ft_putchar('.');
    while (++byte < flags.accuracy)
    {
        real *= 10;
        ft_putnbr((int)real % 10);
    }
}

static int  print_str(char c, va_list arg)
{
    if (c == 'c')
        ft_putchar(va_arg(arg, int));
    else if (c == 's')
        ft_putstr(va_arg(arg, char *));
    if (c == 'p')
        return (0);
    else if (c == '%')
        ft_putchar('%');
    else
        return (0);
    return (1);
}

static char parse_flags_ap(va_list arg)
{
    while (*g_format && !belongs_set(*g_format, SPECIFIIER))
    {
        if (*g_format == 'l')
        {
            if (flags.l)
            {
                flags.l = 0;
                flags.ll = 1;
            }
            else
                flags.l = 1;
        }
        else if (*g_format == 'h')
        {
            if (flags.h)
            {
                flags.h = 0;
                flags.hh = 1;
            }
            else
                flags.h = 1;
        }
        else if (*g_format == '*' || ft_isdigit(*g_format))
            if ((flags.accuracy = ft_atoi(g_format)) == 0)
                flags.accuracy = va_arg(arg, int);
        g_format++;
    }
    return (*g_format);
}

static char parse_flags(va_list arg)
{
    while (*g_format && !belongs_set(*g_format, SPECIFIIER))
    {
        if (*g_format == '0')
            flags.zero = 1;
        else if (*g_format == '+')
            flags.plus = 1;
        else if (*g_format == '-')
            flags.minus = 1;
        else if (*g_format == '#')
            flags.oct = 1;
        else if (*g_format == '*' || ft_isdigit(*g_format))
        {
            if ((flags.width = ft_atoi(g_format)) == 0)
                flags.width = va_arg(arg, int);
        }
        else if (*g_format == '.')
            return parse_flags_ap(arg);
        g_format++;
    }
    return (*g_format);
}

static void reset_flags(void)
{
    flags.zero = 0;
    flags.plus = 0;
    flags.minus = 0;
    flags.oct = 0;
    flags.l = 0;
    flags.ll = 0;
    flags.h = 0;
    flags.hh = 0;
    flags.L = 0;
    flags.width = 0;
    flags.accuracy = 0;
}

static void processing_flags_str(void)
{

}

static void processing_flags_float(void)
{

}

static void processing_flags_int(void)
{

}

void     parse_arg(va_list arg)
{
    char c;

    c = parse_flags(arg);
    ft_putnbr(flags.width);
    if (belongs_set(c, SPECIFIIER_INT))
    {
        processing_flags_int();
        print_int(c, arg);
    }
    else if (belongs_set(c, SPECIFIIER_FLOAT))
    {
        processing_flags_float();
        print_float(va_arg(arg, double));    
    }
    else if (belongs_set(c, SPECIFIIER_STR))
    {
        processing_flags_str();
        print_str(c, arg);
    }
    else 
        return ;
}

static int search_specifier(void)
{
    int i;

    i = 0;
    while (g_format[i] && g_format[i] != '%')
    {
        if (belongs_set(g_format[i], SPECIFIIER))
            return (1);
        i++;
    }
    return (0);
}

int     parse_format(va_list arg)
{
    char *pf;

    while (*g_format)
    {
        if (*g_format == '%')
        {
            g_format++;
            reset_flags();
            if (search_specifier())
                parse_arg(arg);
            else
                ft_putchar('%');
        }
        else
        {
            pf = (char *)g_format;
            while (*g_format && *g_format != '%')
                g_format++;
            write(1, pf, g_format - pf);
        }
        g_format++;
    }
    return (1);
}

int     ft_printf(const char *format, ...)
{
    va_list arg;
    int done;
    g_format = format;

    va_start(arg, format);
    done = parse_format(arg);
    va_end(arg);
    return (done);
}
