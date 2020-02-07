/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reallocate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:38:31 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/07 17:26:35 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int vector_reallocate(t_vector *vector)
{
    t_vector old;

    if (!vector)
        return (VECTOR_ERROR);
    if (vector_init(&old, VECTOR_INCREACE_CAPACITY(vector->capacity, VECTOR_BASE_SPEED), vector->element_size) == VECTOR_ERROR)
        return (VECTOR_ERROR);
    if (vector_copy(&old, vector) == VECTOR_ERROR)
        return (VECTOR_ERROR);
    if (vector_move(vector, &old) == VECTOR_ERROR)
        return (VECTOR_ERROR);
    return (VECTOR_SUCCESS);
}

