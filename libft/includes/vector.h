/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:36:34 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/02/05 19:02:49 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_H__
# define __VECTOR_H__
# include "libft.h"

/*
** --------------------------- DEFINITIONS  ------------------------------------------
*/

# define VECTOR_INCREACE_CAPACITY(size) (sise << 2)
# define VECTOR_MINIMUM_CAPACITY    4
# define VECTOR_SUCCESS             0
# define VECTOR_ERROR               -1

/*
** --------------------------- STRUCTURE --------------------------------------------
*/

typedef struct  s_vector {
	void		*data;
	size_t		size;
	size_t		capacity;
	size_t		element_size;
}               t_vector;

/*
** --------------------------- FUNCTIONS --------------------------------------------
** --------------------------- CONSTRUCTOR ------------------------------------------
*/

int				vector_init(t_vector *vector, size_t capacity, size_t element_size);
int				vector_copy(t_vector *dst, const t_vector *src);

/*
** --------------------------- MOVE ------------------------------------------------
*/

int				vector_move(t_vector *dst, const t_vector *src);
int				vector_swap(t_vector *dst, const t_vector *src);

/*
** --------------------------- INSERTION ------------------------------------------
*/

int				vector_push_back(t_vector *vector, void	*element);
int 			vector_push_front(t_vector *vector, void *element);
int 			vector_insert(t_vector *vector, size_t index, void *element);

/*
** --------------------------- DELETION ------------------------------------------
*/

int				vector_pop_back(t_vector *vector);
int				vector_pop_front(t_vector *vector);
int				vector_erase(t_vector *vector, size_t index);
int				vector_clear(t_vector *vector);
int				vector_dectroy(t_vector *vector);

/*
** --------------------------- INFORMATION ------------------------------------------
*/

bool			vector_is_initialized(const t_vector *vector);
size_t			vector_free_space(const t_vector *vector);
bool			vector_is_empty(const t_vector *vector);
size_t          vector_byte_size(const t_vector *vector);

/*
** --------------------------- MEMORY ----------------------------------------------
*/

int 			vector_resize(t_vector *vector, size_t new_size);
int				vector_reserve(t_vector *vector, size_t minimum_capacity);
int				vector_shrink_to_fit(t_vector *vector);
int             vector_reallocate(t_vector *vector, size_t new_capacity);

#endif
