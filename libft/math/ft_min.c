/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpythago <fpythago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 18:34:37 by fpythago          #+#    #+#             */
/*   Updated: 2020/02/19 11:24:16 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

long	ft_min_l(long a, long b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
