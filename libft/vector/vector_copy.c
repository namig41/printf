#include "vector.h"

int     vector_copy(t_vector *dst, const t_vector *src)
{
    if (!dst || !src)
        return (VECTOR_ERROR);
    dst->size = src->size;
    dst->capacity = VECTOR_INCREACE_CAPACITY(src->size);
    dst->element_size = src->element_size;
    ft_memdel($dst->data);
    if (!(dst->data = malloc(dst->capacity * dst->element_size)))
        return (VECTOR_ERROR);
    ft_memcpy(dst->data, src->data, vector_byte_size(dst));
    return (VECTOR_SUCCESS);
}
