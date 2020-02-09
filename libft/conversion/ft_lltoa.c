/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:58:43 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/08 18:47:37 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_lltoa(long long n)
{
    int     size_str;
    char    *str;
    t_ll 	 n2;

    n2 = (n < 0) ? (t_ull)-n : (t_ll)n;
    size_str = (n < 0) ? 2 : 1;
    while ((n2 /= 10))
        size_str++;
    if (!(str = (char*)malloc(sizeof(*str) * (size_str + 1))))
        return (0);
    str[size_str] = '\0';
    n2 = (n < 0) ? (t_ll)-n : (t_ll)n;
    while (--size_str >= 0)
    {
        str[size_str] = n2 % 10 + '0';
        n2 /= 10;
    }
    str[0] = (n < 0) ? '-' : str[0];
    return (str);
}
