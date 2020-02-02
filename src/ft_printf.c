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

static void m_putstr(char c, int w)
{
	while (w--)
		ft_putchar(c);
}

static void print_oct(char c, char fc)
{
    char    *pref_oct;

    if (g_printf.flags.zero && fc != '0')
    {
        if (c == 'x')
            pref_oct = "0x";
        else if (c == 'X')
            pref_oct = "0X";
        else if (c == 'o')
            pref_oct = "0";
        g_printf.flags.width -= ft_strlen(pref_oct);
        ft_putstr(pref_oct);
    }
}

static void print_pref(char c, char cf)
{
    if (g_printf.flags.zero)
        return ;
	if (c == '-')
		ft_putchar('-');
	else if (g_printf.flags.plus)
		ft_putchar('+');
    else if (g_printf.flags.width == 0)
        ft_putchar(' ');
    else
        return ;
    print_oct(c, cf); 
    g_printf.flags.width -= 1;
}

// l
// ll
// h
// hh

static void handle_int(char c, char *s_int)
{
    m_putstr(' ', g_printf.flags.width - ft_max(g_printf.flags.accuracy, ft_strlen(s_int)));
    print_pref(c, *s_int);
    g_printf.flags.width = (g_printf.flags.width > g_printf.flags.accuracy)
                                ? g_printf.flags.width - ft_strlen(s_int) : g_printf.flags.accuracy;
    m_putstr( g_printf.flags.zero ? '0' : ' ', g_printf.flags.width);
    g_printf.flags.zero = !g_printf.flags.zero;
    print_pref(c, *s_int);
    ft_putstr(s_int + (*s_int == '-' && g_printf.flags.plus));
    m_putstr(' ', g_printf.flags.minus * g_printf.flags.width);
}

//static void processing_int_flag(char c, char *s_int)
//{
//    type_oct(c);
//    g_flags.l = g_flags.zero;
//    if (g_flags.point)
//    {
//        processing_width(' ', g_flags.width - ft_max(g_flags.point, ft_strlen(s_int)) - g_flags.oct);
//        g_flags.minus = processing_sign(s_int[0]);
//        g_flags.width = (g_flags.width > g_flags.point) ? g_flags.width - ft_strlen(s_int) : g_flags.point;
//        processing_width('0', g_flags.width - ft_strlen(s_int) - g_flags.minus - g_flags.oct);
//        print_int(c, s_int + (g_flags.minus && s_int[0] == '-'));
//    }
//    else if (g_flags.minus)
//    {
//        print_oct(c, s_int[0]);
//        print_int(c, s_int);
//        processing_width(' ', g_flags.width - ft_strlen(s_int) - g_flags.oct);
//    }
//    else
//    {
//        g_flags.minus = g_flags.zero ? processing_sign(s_int[0]) : 0;
//        print_oct(c, s_int[0]);
//        processing_width(g_flags.zero ? '0' : ' ', g_flags.width - ft_strlen(s_int) - g_flags.minus - g_flags.oct);
//        print_int(c, s_int + (g_flags.minus && s_int[0] == '-'));
//    }
//}

static void     processing_int(char c, va_list arg)
{
    char *s_int;

    if (c == 'd' || c == 'i')
    {
        if (g_printf.modifiers.ll)
            s_int = ft_lltoa(va_arg(arg, t_ll));
        else if (g_printf.modifiers.l)
            s_int = ft_lltoa(va_arg(arg, t_l));
        else
            s_int = ft_lltoa(va_arg(arg, int));
    }
    else if (c == 'u')
    {
        if (g_printf.modifiers.ll)
            s_int = ft_lltoa(va_arg(arg, t_ull));
        else if (g_printf.modifiers.l)
            s_int = ft_lltoa(va_arg(arg, t_ul));
        else
            s_int = ft_lltoa(va_arg(arg, t_ui));
    }
    else if (c == 'o')
    { 
        if (g_printf.modifiers.ll)
            s_int = ft_ulltoa_base(va_arg(arg, t_ull), 8, 'o');
        else if (g_printf.modifiers.l)
            s_int = ft_ulltoa_base(va_arg(arg, t_ul), 8, 'o');
        else
            s_int = ft_uitoa_base(va_arg(arg, int), 8, 'o');
    }
    else if (c == 'x')
    {
        if (g_printf.modifiers.ll)
            s_int = ft_ulltoa_base(va_arg(arg, t_ull), 16, 'x');
        else if (g_printf.modifiers.l)
            s_int = ft_ulltoa_base(va_arg(arg, t_ul), 16, 'x');
        else
            s_int = ft_uitoa_base(va_arg(arg, int), 16, 'x');
    }
    else if (c == 'X')
    {
        if (g_printf.modifiers.ll)
            s_int = ft_ulltoa_base(va_arg(arg, t_ull), 16, 'X');
        else if (g_printf.modifiers.l)
            s_int = ft_ulltoa_base(va_arg(arg, t_ul), 16, 'X');
        else
            s_int = ft_uitoa_base(va_arg(arg, int), 16, 'X');
    }
    else
        return ;
    handle_int(c, s_int);
    free(s_int);
}

static void  print_float(double real)
{
    int byte;

    byte = -1;
    if (!g_printf.flags.accuracy)
        g_printf.flags.accuracy = 6;
    ft_putnbr((t_ui)real);
    ft_putchar('.');
    while (++byte < g_printf.flags.accuracy)
    {
        real *= 10;
        ft_putnbr((int)real % 10);
    }
}
static void p_str_flag(char *s_str)
{
    if (g_printf.flags.minus)
    {
        m_putstr(s_str, 0, g_printf.flags.accuracy);
        m_putstr(' ', g_printf.flags.width - ft_strlen(s_str));
    }
    else
    {
		m_putstr(' ', g_printf.flags.width - ft_strlen(s_str));
		m_putstr(s_str, g_printf.flags.accuracy);
    }
}

static int  processing_str(char c, va_list arg)
{
    char *s_str;

    if (c == 'c')
    {
        if (g_printf.flags.minus)
        {
            ft_putchar(va_arg(arg, int));
			m_putstr(0, ' ', g_printf.flags.width - 1);
        }
        else
        {
			m_putstr(0, ' ', g_printf.flags.width - 1);
            ft_putchar(va_arg(arg, int));
        }
        return ;
    }
    else if (c == 's')
        s_str = va_arg(arg, char *);
    if (c == 'p')
        s_str = va_arg(arg, char *);
    p_str_flag(s_str);
}

static int	p_star(va_list arg)
{
	if (*g_printf.format == '*')
	{
		g_printf.format++;
		return va_arg(arg, int);
	}
	else if (ft_isdigit(*g_printf.format))
		return ft_atoi(g_printf.format);
	return (0);
}

static char parse_flags(va_list arg)
{
    while (*g_printf.format)
    {
        if (*g_printf.format == '0')
            g_printf.flags.zero = 1;
        else if (*g_printf.format == ' ')
            g_printf.flags.space = 1;
        else if (*g_printf.format == '+')
            g_printf.flags.plus = 1;
        else if (*g_printf.format == '-')
            g_printf.flags.minus = 1;
        else if (*g_printf.format == '#')
            g_printf.flags.oct = 1;
        else if (*g_printf.format == 'l')
			g_printf.modifiers.l = (g_printf.modifiers.ll = g_printf.modifiers.l) ? 0 : 1;
        else if (*g_printf.format == 'h')
			g_printf.modifiers.h = (g_printf.modifiers.hh = g_printf.modifiers.h) ? 0 : 1;
		else if ((g_printf.flags.width = p_star(arg)))
			;
        else if (*g_printf.format == '.' && (g_printf.flags.accuracy = p_star(arg)))
			;
        g_printf.format++;
    }
    return (*g_printf.format);
}

void     parse_arg(va_list arg)
{
    char c;

    c = parse_flags(arg);
    if (c == -1)
    	return ;
    else if (c == '%')
        ft_putchar('%');
    else if (ft_strchr(SPEC_INT, c))
    {
        processing_int(c, arg);
    }
    else if (ft_strchr(SPEC_FLOAT, c))
    {
        print_float(va_arg(arg, double));    
    }
    else if (ft_strchr(SPEC_STR, c))
    {
		processing_str(c, arg);
    }
}

static int	search_specifier(void)
{
	size_t	i;

    i = 0;
    while (g_printf.format[i] && g_printf.format[i] != '%')
    {
        if (ft_strchr(ASPEC, g_printf.format[i]))
            return (1);
        i++;
    }
    return (0);
}

void            parse_format(va_list arg)
{
    while (*g_printf.format)
    {
        if (*g_printf.format == '%')
        {
            g_printf.format++;
            ft_bzero(&g_printf.flags, sizeof(g_printf.flags));
	        ft_bzero(&g_printf.modifiers, sizeof(g_printf.modifiers));
            if (search_specifier())
				parse_arg(arg);
            else
                ft_putchar('%');
        }
        else
        {
            while (*g_printf.format && *g_printf.format != '%')
                ft_putchar(*g_printf.format);
            g_printf.format--;
        }
        g_printf.format++;
    }
}

int         ft_printf(const char *format, ...)
{
    va_list arg;

    g_printf.format = format;
    va_start(arg, format);
    parse_format(arg);
    va_end(arg);
    return (g_printf.done);
}
