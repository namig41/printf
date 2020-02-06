#include "vector.h"

int     vector_init(t_vector *vector, size_t capacity, size_t element_size)
{
    if (!vector)
        return (VECTOR_ERROR);
    vector->size = 0;
    vector->capacity = FT_MIN(VECTOR_MINIMUM_CAPACITY, capacity);
    vector->element_size = element_size;
    if (!(vector->data = malloc(vector->capacity * vector->element_size))
        return (VECTOR_ERROR);
    return (VECTOR_SECCESS);
}

