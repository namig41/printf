#include "vector.h"

int vector_reallocate(t_vector *vector)
{
    t_vector old;

    if (!vector)
        return (VECTOR_ERROR);
    if (vector_init(&old, VECTOR_INCREASE(vector->capacity)) == VECTOR_ERROR)
        return (VECTOR_ERROR);
    if (vector_copy(&old, vector) == VECTOR_ERROR)
        return (VECTOR_ERROR);
    if (vector_move(vector, &old) == VECTOR_ERROR)
        return (VECTOR_ERROR);
    return (VECTOR_SUCCESS);
}

