#include "vector.h"

int vector_move(t_vector *dst, const t_vector *src)
{
    if (vector_destroy(dst) == VECTOR_ERROR || !src)
        return (VECTOR_ERROR);
    *dst = *src;
    src->data = 0;
    return (VECTOR_SUCCESS);
}
