/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_offset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpythago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:27:47 by fpythago          #+#    #+#             */
/*   Updated: 2020/02/11 20:13:53 by fpythago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void		*vector_offset(t_vector *vector, size_t index)
{
	return (vector->data + (vector->element_size * index));
}

void			l_vector_offset(t_vector *vector,
					size_t index, void *element, t_uc offset_flag)
{
	if (offset_flag == OFFSET_NO)
		ft_memcpy(vector_offset(vector, index), element, vector->element_size);
	else if (offset_flag == OFFSET_RIGHT)
	{
		ft_memmove(vector_offset(vector, index + 1),
			vector_offset(vector, index),
				vector->element_size * (vector->size - index));
		ft_memcpy(vector_offset(vector, index), element, vector->element_size);
	}
	else if (offset_flag == OFFSET_LEFT)
		ft_memmove(vector_offset(vector, index),
				vector_offset(vector, index + 1),
					vector->element_size * (vector->size - index));
}
