/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_pop_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:46:57 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/11 20:15:55 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vector_pop_front(t_vector *vector)
{
	void *element;

	if (!vector)
		return (NULL);
	element = vector->data;
	l_vector_offset(vector, 0, NULL, OFFSET_LEFT);
	vector->size--;
	return (element);
}
