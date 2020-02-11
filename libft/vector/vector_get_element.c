/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_get_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:40:43 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/11 19:15:30 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vector_get_element(t_vector *vector, size_t index)
{
	if (!vector && vector->size < index)
		return (NULL);
	return (vector->data + (index * vector->element_size));
}
