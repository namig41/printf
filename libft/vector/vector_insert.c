/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:37:40 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/07 15:54:23 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int vector_insert(t_vector *vector, size_t index, void *element)
{
    if (!vector || !element || vector->size < index)
        return (VECTOR_ERROR);
    if (vector->size == vector->capacity &&
        vector_reallocate(vector) == VECTOR_ERROR)
        return (VECTOR_ERROR);
    _vector_offset(vector, index, element, OFFSET_RIGHT);
    vector->size++;
    return (VECTOR_SUCCESS);
}
