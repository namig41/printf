/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_get_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpythago <fpythago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:40:43 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/17 15:37:04 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vector_get_element(t_vector *vector, size_t index)
{
	if (!vector && vector->size < index)
		return (NULL);
	return (vector->data + (index * vector->element_size));
}
