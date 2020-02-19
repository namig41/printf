/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpythago <fpythago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:34 by ngale             #+#    #+#             */
/*   Updated: 2020/02/19 13:54:22 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	round_digit(char *str_float, t_vector *vec_float, t_ll i, t_l preci)
{
	if (str_float[i] == '5' && preci == STD_PRECI)
	{
		i--;
		if (((str_float[i] - '0') & 1) && str_float[i] < '9')
			str_float[i]++;
	}
	else if (str_float[i] > '4')
	{
		i--;
		while (str_float[i] == '9' || str_float[i] == '.')
			(str_float[i] != '.') ? str_float[i--] = '0' : i--;
		(i < 0) ? vector_push_front(vec_float, "1") : str_float[i]++;
		str_float = (char *)vec_float->data;
	}
	return (i < 0);
}

void		round_precision(t_printf *p, char *str_float, t_vector *vec_float)
{
	size_t i;

	if (p->f & F_PRECI)
	{
		i = ft_strchri(str_float, '.') + 1;
		i += round_digit(str_float, vec_float, i, p->precision);
		p->precision = 0;
		str_float[i - 1 + ((p->f & F_SHARP) != 0)] = '\0';
		p->f &= ~F_PRECI;
	}
	else
	{
		i = ft_strchri(str_float, '.') + p->precision + 1;
		round_digit(str_float, vec_float, i, p->precision);
		str_float[i] = '\0';
	}
	p->len = ft_strlen(str_float);
}
