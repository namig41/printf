#include "vector.h"

int vector_insert(t_vector *vector, size_t index, void *element)
{
    if (!vector || !element || vector->size < index)
        return (VECTOR_ERROR);
}
