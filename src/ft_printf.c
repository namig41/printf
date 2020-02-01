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

static void m_putstr(char *s, char c, int w)
{
	size_t i;
	size_t len;

	i = 0;
	if (s)
	{
		len = ft_min(ft_strlen(s), w);
		while (i < len)
		{
			ft_putchar(s[i]);
			i++;
		}
	}
	else
	{
		while (i < w)
		{
			ft_putchar(c);
			i++;
		}
	}
}

static void type_oct(char c)
{
    if (g_flags.oct)
    {
        g_flags.oct = 0;
        if (c == 'x' || c == 'X')
            g_flags.oct = 2;
        else if (c == 'o')
            g_flags.oct = 1;
    }
}

static void print_oct(char c, char s)
{
    if (g_flags.oct && g_flags.zero && s != '0')
    {
        if (c == 'x')
            ft_putstr("0x");
        else if (c == 'X')
            ft_putstr("0X");
        else if (c == 'o')
            ft_putchar('0');
    }
}

static void print_int(char *s_int)
{
    if (s_int[0] != '-' && g_flags.plus && g_flags.zero)
        ft_putchar('+');
    ft_putstr(s_int);
}

static void processing_sign(char c)
{
	if (g_flags.zero)
	{
		if (c == '-')
			ft_putchar('-');
		else if (g_flags.plus)
			ft_putchar('+');
	}
}

// l
// ll
// h
// hh
static void processing_int_flag2(char c, char *s_int)
{

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



static void  processing_int(char c, va_list arg)
{
    char *s_int;

    if (c == 'd' || c == 'i')
    {
        if (g_modifiers.ll)
            s_int = ft_lltoa(va_arg(arg, t_ll));
        else if (g_modifiers.l)
            s_int = ft_lltoa(va_arg(arg, t_l));
        else
            s_int = ft_lltoa(va_arg(arg, int));
    }
    else if (c == 'u')
    {
        if (g_modifiers.ll)
            s_int = ft_lltoa(va_arg(arg, t_ull));
        else if (g_modifiers.l)
            s_int = ft_lltoa(va_arg(arg, t_ul));
        else
            s_int = ft_lltoa(va_arg(arg, t_ui));
    }
    else if (c == 'o')
    { 
        if (g_modifiers.ll)
            s_int = ft_ulltoa_base(va_arg(arg, t_ull), 8, 'o');
        else if (g_modifiers.l)
            s_int = ft_ulltoa_base(va_arg(arg, t_ul), 8, 'o');
        else
            s_int = ft_uitoa_base(va_arg(arg, int), 8, 'o');
    }
    else if (c == 'x')
    {
        if (g_modifiers.ll)
            s_int = ft_ulltoa_base(va_arg(arg, t_ull), 16, 'x');
        else if (g_modifiers.l)ё
            s_int = ft_ulltoa_base(va_arg(arg, t_ul), 16, 'x');
        else
            s_int = ft_uitoa_base(va_arg(arg, int), 16, 'x');
    }
    else if (c == 'X')
    {
        if (g_modifiers.ll)
            s_int = ft_ulltoa_base(va_arg(arg, t_ull), 16, 'X');
        else if (g_modifiers.l)
            s_int = ft_ulltoa_base(va_arg(arg, t_ul), 16, 'X');
        else
            s_int = ft_uitoa_base(va_arg(arg, int), 16, 'X');
    }
    processing_int_flag(c, s_int);
    free(s_int);
}

static void  print_float(double real)
{
    int byte;

    byte = -1;
    if (!g_flags.point)
        g_flags.point = 6;
    ft_putnbr((t_ui)real);
    ft_putchar('.');
    while (++byte < g_flags.point)
    {
        real *= 10;
        ft_putnbr((int)real % 10);
    }
}
static void p_str_flag(char *s_str)
{
    if (g_flags.minus)
    {
        m_putstr(s_str, 0, g_flags.accuracy);
        m_putstr(0, ' ', g_flags.width - ft_strlen(s_str));
    }
    else
    {
		m_putstr(0, ' ', g_flags.width - ft_strlen(s_str));
		m_putstr(s_str, 0, g_flags.accuracy);
    }
}

static int  p_str(char c, va_list arg)
{
    char *s_str;

    if (c == 'c')
    {
        if (g_flags.minus)
        {
            ft_putchar(va_arg(arg, int));
			m_putstr(0, ' ', g_flags.width - 1);
        }
        else
        {
			m_putstr(0, ' ', g_flags.width - 1);
            ft_putchar(va_arg(arg, int));
        }
        return (1);
    }
    else if (c == 's')
        s_str = va_arg(arg, char *);
    if (c == 'p')
        s_str = va_arg(arg, char *);
    processing_str_flag(s_str);
    return (1);
}

static int	p_star(void)
{
	if (*g_format == '*')
	{
		g_format++;
		return va_arg(arg, int);
	}
	else if (ft_isdigit(*g_format))
		return ft_atoi(g_format);
	return (0);
}

static char parse_flags(va_list arg)
{
    while (*g_format)
    {
        if (*g_format == '0')
            g_flags.zero = 1;
        else if (*g_format == '+')
            g_flags.plus = 1;
        else if (*g_format == '-')
            g_flags.minus = 1;
        else if (*g_format == '#')
            g_flags.oct = 1;
        else if (*g_format == 'l')
			g_modifiers.l = (g_modifiers.ll = g_modifiers.l) ? 0 : 1;
        else if (*g_format == 'h')
			g_modifiers.h = (g_modifiers.hh = g_modifiers.h) ? 0 : 1;
		else if ((g_flags.width = p_star()))
			;
        else if (*g_format == '.' && (g_flags.accurancy = p_star()))
			;
        else
        	return (-1);
        g_format++;
    }
    return (*g_format);
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
        p_int(c, arg);
    }
    else if (ft_strchr(SPEC_FLOAT, c))
    {
        print_float(va_arg(arg, double));    
    }
    else if (ft_strchr(SPEC_STR, c))
    {
        p_str(c, arg);
    }
}

static int	search_specifier(void)
{
	size_t	i;

    i = 0;
    while (g_format[i] && g_format[i] != '%')
    {
        if (belongs_set(ASPEC, g_format[i]))
            return (1);
        i++;
    }
    return (0);
}

static void 	update(void)
{
	ft_bzero(&g_flags, sizeof(g_flags));
	ft_bzero(&g_modifiers, sizeof(g_modifiers));
}

int     		parse_format(va_list arg)
{
    while (*g_format)
    {
        if (*g_format == '%')
        {
            update();
			g_format++;
            if (search_specifier())
				parse_arg(arg);
            else
                ft_putchar('%');
        }
        else
        {
            while (*g_format && *g_format != '%')
                ft_putchar(*g_format);
            g_format--;
        }
        g_format++;
    }
    return (1);
}

int     ft_printf(const char *format, ...)
{
    va_list arg;
    int		done;

    g_format = format;
    va_start(arg, format);
    done = parse_format(arg);
    va_end(arg);
    return (done);
}
