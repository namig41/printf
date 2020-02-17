/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpythago <fpythago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:42:23 by fpythago          #+#    #+#             */
/*   Updated: 2020/02/17 16:52:55 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "vector.h"
#include <stdio.h>

void	print_byte(char byte)
{
	int i;

	i = 0;
	while (i < 8)
	{
		printf("%d", ((byte & (1 << i)) != 0));
		i++;
	}
}

int			main(void)
{
	t_float	m_float;

	m_float.ld_float = -4.4;
	for (int i = 0; i < 16; i++)
	{
		printf("byte %d\t", i);	
		print_byte(m_float.c_float[i]);
		printf("\n");
	}
	t_float_flags flags;
	flags.sign = (t_uc)(m_float.c_float[9] >> 8) != 0;
	printf("%d\n", flags.sign);
	flags.exp = (t_uc)m_float.c_float[8];
	flags.exp = flags.exp << 7 | (t_uc)m_float.c_float[9] >> 7;
	for (int i = 0; i < 15; i++)
	{
		printf("%d", (flags.exp & (1 << i)) != 0);
	}
	printf("\n");
	return (0);
}
