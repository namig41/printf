/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:34 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/05 19:22:38 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF__
# define __FT_PRINTF__
# include <stdarg.h>
# include "libft.h"
/*
** --------------------------- FLAGS MASKS ---------------------------------------------
*/
# define FLAGS		" +-#0*"
# define F_SPACE 	(1 << 0)
# define F_PLUS		(1 << 1)
# define F_MINUS	(1 << 2)
# define F_SHARP	(1 << 3)
# define F_ZERO		(1 << 4)
# define F_WILDCARD	(1 << 5)
# define F_PRECI	(1 << 6)
# define F_UPCASE	(1 << 7)
/*
** --------------------------- MODIFERS MASKS ------------------------------------------
*/
# define MODIFERS	"hl"
# define M_SHORT	(1 << 0)
# define M_SHORT_2	(1 << 1)
# define M_LONG		(1 << 2)
# define M_LONG_2	(1 << 3)
/*
** --------------------------- ALL SPECIFIER ------------------------------------------
*/
# define S_INT		"dDi"
# define S_UINT		"uU"
# define S_HEX		"xXp"
# define S_OCT		"oO"
# define S_FLOAT	"fF"
# define S_CHAR		"cC"
# define S_STR 		"sS"
# define PERCENT	"%"
/*
** --------------------------- NUMBER SYSTEM ------------------------------------------
*/
# define BASE_16	16
# define BASE_10    10
# define BASE_8		8
/*
** --------------------------- OTHER ------------------------------------------
*/
# define STR_NULL "(null)"

typedef struct	s_printf
{
	t_uc		m;
	t_si		f;
	t_uc		c;
	t_ui		len;
	t_ui		width;
	t_l			precision;
	char		*format;
	va_list 	arg;
	t_l			done;
}				t_printf;

/*
** --------------------------- FUNCTIONS ------------------------------------------
*/
int				ft_printf(const char *format, ...);
void			parse_format(t_printf *);
#endif
