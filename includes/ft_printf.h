/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:49:34 by lcarmelo          #+#    #+#             */
/*   Updated: 2019/11/21 13:49:35 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF__
# define __FT_PRINTF__
# include <stdarg.h>
# include "libft.h"
# define ASPEC "fdiouxXcsp"
# define FM "#+-0hl*"
# define SPEC_INT "diouxX"
# define SPEC_FLOAT "f"
# define SPEC_STR "csp"

typedef struct	s_flags
{
	int			zero;
	int 		plus;
	int			minus;
	int			oct;
	int			width;
	int			accuracy;
	int			space;
}				t_flags;

typedef struct 	s_modifier
{
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			L;
}				t_modifier;

typedef struct	s_printf
{
	t_modifier	modifiers;
	t_flags		flags;
	const char	*format;
	int			done;
}				t_printf;

int				ft_printf(const char *format, ...);
void			parse_format(va_list arg);
void			parse_arg(va_list arg);

t_printf g_printf;
#endif
