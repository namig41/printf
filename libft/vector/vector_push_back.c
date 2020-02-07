#include "vector.h"

int vector_push_back(t_vector *vector, void *element)
{
    if (!vector || !element)
        return (VECTOR_ERROR);
    if (vector->size > vector->capacity &&
        vector_reallocate(vector) == VECTOR_ERROR)
       return (VECTOR_ERROR); 
    vector_add_element(vector, vector->size++, element);
    return (VECTOR_SUCCESS);
}
