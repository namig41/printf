#include "vector.h"

size_t vector_byte_size(const t_vector *vector)
{
    return (vector) ? (vector->size * vector->element_size) : 0;
}
