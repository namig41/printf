/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:12:19 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/07 16:14:57 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int vector_clear(t_vector *vector)
{
    if (!vector)
        return (VECTOR_ERROR);
    ft_bzero(vector->data, vector_byte_size(vector));
    return (VECTOR_SUCCESS);
}

