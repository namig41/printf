/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:16:05 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/11 16:26:31 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int     vector_init(t_vector *vector, size_t capacity, size_t element_size)
{
    if (!vector)
        return (VECTOR_ERROR);
    vector->size = 0;
    vector->capacity = FT_MAX(VECTOR_MIN_CAPACITY, capacity);
    vector->element_size = element_size;
    if (!(vector->data = malloc(vector->capacity * vector->element_size)))
        return (VECTOR_ERROR);
    return (VECTOR_SUCCESS);
}

