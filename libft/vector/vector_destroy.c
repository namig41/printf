#include "vector.h"

int vector_destroy(t_vector *vector)
{
    if (!vector)
        return (VECTOR_ERROR);
    ft_memdel(&vector->data);
    return (VECTOR_SUCCESS);
}

