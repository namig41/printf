/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:38:06 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/11 17:21:33 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int vector_push_back(t_vector *vector, void *element)
{
    if (!vector || !element)
        return (VECTOR_ERROR);
    if (vector->size == vector->capacity && !vector_reallocate(vector))
    	return (VECTOR_ERROR); 
    _vector_offset(vector, vector->size, element, OFFSET_NO);
    vector->size++;
    return (VECTOR_SUCCESS);
}
