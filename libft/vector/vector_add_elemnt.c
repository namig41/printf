#include "vector.h"

static void    *vector_offset(t_vector *vector, size_t index)
{
    return vector->data + (vector->element_size * index);
}

void            _vector_add_element(t_vector *vector, size_t index, void *element);
{
    ft_memcpy(vector_offset(vector, index), element, vector->element_size);
}
