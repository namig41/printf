/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:38:06 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/07 16:01:30 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int vector_push_back(t_vector *vector, void *element)
{
    if (!vector || !element)
        return (VECTOR_ERROR);
    if (vector->size == vector->capacity &&
        vector_reallocate(vector) == VECTOR_ERROR)
    return (VECTOR_ERROR); 
    _vector_offset(vector, vector->size, element, OFFSET_NO);
    vector->size++;
    return (VECTOR_SUCCESS);
}
