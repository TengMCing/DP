//
// Created by Patrick Li on 9/7/22.
//

#include "vector.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector_p new_vector(VEC_TYPE vec_type)
{
    // Allocate memory for the struct
    vector_p vector = malloc(sizeof(vector_t));
    vector->capacity = 10;
    vector->size = 0;
    vector->type = vec_type;
    vector->copy_type = VEC_ORIGINAL;
    for (int i = 0; i < MAX_VEC_NAME_LEN; i++)
        vector->name[i] = '\0';

    // Allocate memory for the container
    switch (vec_type)
    {
    case VEC_INT:
        vector->data = calloc(vector->capacity, sizeof(int));
        break;
    case VEC_FLOAT:
        vector->data = calloc(vector->capacity, sizeof(float));
        break;
    case VEC_DOUBLE:
        vector->data = calloc(vector->capacity, sizeof(double));
        break;
    case VEC_CHAR:
        vector->data = calloc(vector->capacity, sizeof(char));
        break;
    case VEC_VEC_P:
        vector->data = calloc(vector->capacity, sizeof(vector_p));
        break;
    default:
        UndefinedTypeError;
    }

    return vector;
}

void delete_vector(vector_p vector)
{
    if (vector->copy_type == VEC_SHALLOW_COPY)
    {
        delete_copy(vector);
        return;
    }

    // Deallocate the memory for the inner vectors
    if (vector->type == VEC_VEC_P)
    {
        vector_p *vec_p_arr = (vector_p *) vector->data;
        for (int i = 0; i < vector->size; i++)
            delete_vector(vec_p_arr[i]);
    }

    // If type == VEC_VEC_P, deallocate the memory for storing the pointers to vector
    // Otherwise, deallocate the memory of an (int/float/double/char) array
    free(vector->data);

    // Deallocate the memory of the struct
    free(vector);
}

void *get(vector_p vector, int index)
{
    if (index >= vector->size || index < 0)
        IndexOutOfBoundError;

    switch (vector->type)
    {

    // Get the address of the item in an array
    case VEC_INT:
        return ((int *) vector->data) + index;
    case VEC_FLOAT:
        return ((float *) vector->data) + index;
    case VEC_DOUBLE:
        return ((double *) vector->data) + index;
    case VEC_CHAR:
        return ((char *) vector->data) + index;

    // Get what it points to
    case VEC_VEC_P:
        return ((vector_p *) vector->data)[index];
    default:
        UndefinedTypeError;
    }
}

vector_p set(vector_p vector, int index, ...)
{
    if (index >= vector->size || index < 0)
        IndexOutOfBoundError;

    va_list ap;
    va_start(ap, index);

    switch (vector->type)
    {
    case VEC_INT:
        set_int(vector, index, va_arg(ap, int));
        break;
    case VEC_FLOAT:
        set_float(vector, index, (float) va_arg(ap, double));
        break;
    case VEC_DOUBLE:
        set_double(vector, index, va_arg(ap, double));
        break;
    case VEC_CHAR:
        set_char(vector, index, (char) va_arg(ap, int));
        break;
    case VEC_VEC_P:
    {
        // Get the old vector
        vector_p old_v = get_vector_p(vector, index);
        vector_p new_v = va_arg(ap, vector_p);

        // If both pointer points to the same vector
        if (old_v == new_v)
            return vector;

        // Delete the old vector if it is not a NULL pointer
        if (old_v != NULL)
            delete_vector(old_v);

        // Assign the new pointer to the array
        set_vector_p(vector, index, new_v);
        break;
    }
    default:
        UndefinedTypeError;
    }

    va_end(ap);
    return vector;
}


// Add constant to a vector
const_op(+, add);

// Subtract a constant from a vector
const_op(-, sub);

// Multiply constant to a vector
const_op(*, mul);

// Divide a vector by a constant
const_op(/, div);

void print_vector_(vector_p vector, unsigned char depth)
{
    printf("[");

    switch (vector->type)
    {
    case VEC_INT:
        for (int i = 0; i < vector->size; i++)
            printf("%i, ", get_int(vector, i));
        break;
    case VEC_FLOAT:
        for (int i = 0; i < vector->size; i++)
            printf("%.3f, ", get_float(vector, i));
        break;
    case VEC_DOUBLE:
        for (int i = 0; i < vector->size; i++)
            printf("%.3f, ", get_double(vector, i));
        break;
    case VEC_CHAR:
        printf("\"%s\"  ", ((char *) vector->data));
        break;
    case VEC_VEC_P:
        if (depth <= 1)
            printf("<VEC_P>: %d  ", vector->size);
        else
        {
            for (int i = 0; i < vector->size; i++)
            {
                print_vector_(get_vector_p(vector, i), depth - 1);
                printf(", ");
            }
        }
        break;
    default:
        UndefinedTypeError;
    }

    if (vector->size > 0 || (vector->type == VEC_VEC_P && depth <= 1))
        printf("\b\b");

    printf("]");
}


vector_p resize(vector_p vector, int size)
{
    if (vector->capacity >= size)
        return vector;

    while (vector->capacity < size)
        vector->capacity *= 2 + 8;

    switch (vector->type)
    {
    case VEC_INT:
        resize_realloc(vector->data, int, vector->capacity);
        break;
    case VEC_FLOAT:
        resize_realloc(vector->data, float, vector->capacity);
        break;
    case VEC_DOUBLE:
        resize_realloc(vector->data, double, vector->capacity);
        break;
    case VEC_CHAR:
        resize_realloc(vector->data, char, vector->capacity);
        break;
    case VEC_VEC_P:
        resize_realloc(vector->data, vector_p, vector->capacity);
        break;
    default:
        UndefinedTypeError;
    }

    return vector;
}


vector_p push(vector_p vector, ...)
{
    va_list ap;
    va_start(ap, vector);

    resize(vector, vector->size + 1);

    switch (vector->type)
    {
    case VEC_INT:
        set_int(vector, vector->size, va_arg(ap, int));
        break;
    case VEC_FLOAT:
        set_float(vector, vector->size, (float) va_arg(ap, double));
        break;
    case VEC_DOUBLE:
        set_double(vector, vector->size, va_arg(ap, double));
        break;
    case VEC_CHAR:
        set_char(vector, vector->size, (char) va_arg(ap, int));
        break;
    case VEC_VEC_P:
        set_vector_p(vector, vector->size, va_arg(ap, vector_p));
        break;
    default:
        UndefinedTypeError;
    }

    va_end(ap);
    vector->size += 1;
    return vector;
}


vector_p push_many(vector_p vector, int num_item, ...)
{
    va_list ap;
    va_start(ap, num_item);

    resize(vector, vector->size + num_item);

    switch (vector->type)
    {
    case VEC_INT:
        for (int i = vector->size; i < vector->size + num_item; i++)
            set_int(vector, i, va_arg(ap, int));
        break;
    case VEC_FLOAT:
        for (int i = vector->size; i < vector->size + num_item; i++)
            set_float(vector, i, (float) va_arg(ap, double));
        break;
    case VEC_DOUBLE:
        for (int i = vector->size; i < vector->size + num_item; i++)
            set_double(vector, i, va_arg(ap, double));
        break;
    case VEC_CHAR:
        for (int i = vector->size; i < vector->size + num_item; i++)
            set_char(vector, i, (char) va_arg(ap, int));
        break;
    case VEC_VEC_P:
        for (int i = vector->size; i < vector->size + num_item; i++)
            set_vector_p(vector, i, va_arg(ap, vector_p));
        break;
    default:
        UndefinedTypeError;
    }

    va_end(ap);
    vector->size += num_item;
    return vector;
}

vector_p pop(vector_p vector, int index)
{
    if (vector->size <= index || index < 0)
        IndexOutOfBoundError;

    switch (vector->type)
    {
    case VEC_INT:
        pop_int(vector, index);
        break;
    case VEC_FLOAT:
        pop_float(vector, index);
        break;
    case VEC_DOUBLE:
        pop_double(vector, index);
        break;
    case VEC_CHAR:
        pop_char(vector, index);
        break;
    case VEC_VEC_P:
        // Delete the inner vector
        delete_vector(get_vector_p(vector, index));
        pop_vector_p(vector, index);
        break;
    default:
        UndefinedTypeError;
    }

    return vector;
}
//
//vector_p pop_many(vector_p vector, int num_item, ...)
//{
//    if (num_item > vector->size)
//        IndexOutOfBoundError;
//
//    va_list ap;
//    va_start(ap, num_item);
//    int *indices = calloc(num_item, sizeof(int));
//    for (int i = 0; i < num_item; i++)
//        indices[i] = va_arg(ap, int);
//    va_end(ap);
//
//    vector_p tmp_vec = new_vector(vector->type);
//    resize(tmp_vec, vector->capacity);
//
//    for (int i = 0; i < vector->size; i++)
//    {
//        unsigned char index_in = 0;
//        for (int j = 0; j < num_item; j++)
//        {
//            if (i == indices[j])
//            {
//                index_in = 1;
//                break;
//            }
//        }
//
//        if (index_in == 0)
//            push(tmp_vec, get(vector, i));
//    }
//
//    vector->size -= num_item;
//
//    return vector;
//}

unsigned int bytes_capacity(vector_p vector)
{
    switch (vector->type)
    {
    case VEC_INT:
        return vector->capacity * sizeof(int);
    case VEC_FLOAT:
        return vector->capacity * sizeof(float);
    case VEC_DOUBLE:
        return vector->capacity * sizeof(double);
    case VEC_CHAR:
        return vector->capacity * sizeof(char);
    case VEC_VEC_P:
        return vector->capacity * sizeof(vector_p);
    default:
        UndefinedTypeError;
    }
}

unsigned int bytes_size(vector_p vector)
{
    switch (vector->type)
    {
    case VEC_INT:
        return vector->size * sizeof(int);
    case VEC_FLOAT:
        return vector->size * sizeof(float);
    case VEC_DOUBLE:
        return vector->size * sizeof(double);
    case VEC_CHAR:
        return vector->size * sizeof(char);
    case VEC_VEC_P:
        return vector->size * sizeof(vector_p);
    default:
        UndefinedTypeError;
    }
}

vector_p copy(vector_p vector)
{
    vector_p copy_v = new_vector(vector->type);
    resize(copy_v, vector->capacity);
    copy_v->size = vector->size;
    copy_v->copy_type = VEC_SHALLOW_COPY;
    unsigned int size = bytes_size(vector);
    if (size > 0)
        memcpy(copy_v->data, vector->data, size);
    return copy_v;
}

void delete_copy(vector_p vector)
{
    free(vector->data);
    free(vector);
}

vector_p deepcopy(vector_p vector)
{
    if (vector->type == VEC_VEC_P)
    {
        // Get a shallow copy
        vector_p copy_v = copy(vector);
        copy_v->copy_type = VEC_ORIGINAL;

        // Fill the content with deep copies
        for (int i = 0; i < vector->size; i++)
            set_vector_p(copy_v, i, deepcopy(get_vector_p(vector, i)));
        return copy_v;
    }
    else
        return copy(vector);
}
