#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "vector.h"

// Vector constructor
// Initial capacity is 10
vector_p new_vector(VEC_TYPE type)
{
    // Allocate memory for the struct
    vector_p v = malloc(sizeof(vector_t));
    v->capacity = 10;
    v->size = 0;
    v->type = type;

    // Allocate memory for the container
    // Array of integers
    if (type == VEC_INT)
        v->data = calloc(v->capacity, sizeof(int));

    // Array of floats
    if (type == VEC_FLOAT)
        v->data = calloc(v->capacity, sizeof(float));

    // Array of doubles
    if (type == VEC_DOUBLE)
        v->data = calloc(v->capacity, sizeof(double));

    // Array of chars
    if (type == VEC_CHAR)
        v->data = calloc(v->capacity, sizeof(char));

    // Array of pointers to vector
    if (type == VEC_VEC_P)
        v->data = calloc(v->capacity, sizeof(vector_p));

    return v;
}

// Vector destroyer
void delete_vector(vector_p v)
{
    // Deallocate the memory of the inner vectors
    if (v->type == VEC_VEC_P)
    {
        vector_p *vec_p_arr = (vector_p *)v->data;
        for (int i = 0; i < v->size; i++)
            delete_vector(vec_p_arr[i]);
    }

    // If type == VEC_VEC_P, deallocate the memory for storing the pointers to vector
    // Ohterwise, deallocate the memory of an (int/float/double/char) array
    free(v->data);

    // Deallocate the memory of the struct
    free(v);
}

// Get an item of a vector
// This returns a memory address to an (int/float/double/char) or
// returns the pointer to the inner vector
void *get(vector_p v, int idx)
{
    if (idx >= v->size || idx < 0)
    {
        printf("ERROR: Index %d out of bound!", idx);
        exit(1);
    }

    // Get the address of the item in an array
    if (v->type == VEC_INT)
        return ((int *)v->data) + idx;
    if (v->type == VEC_FLOAT)
        return ((float *)v->data) + idx;
    if (v->type == VEC_DOUBLE)
        return ((double *)v->data) + idx;
    if (v->type == VEC_CHAR)
        return ((char *)v->data) + idx;

    // Get what it points to
    if (v->type == VEC_VEC_P)
        return ((vector_p *)v->data)[idx];

    return NULL;
}

// Assign value to an item of a vector
// NOTE: replace an existing vector with another vector can be problematic
// if there are still pointers point to the existing vector
void set(vector_p v, int idx, ...)
{
    if (idx >= v->size || idx < 0)
    {
        printf("ERROR: Index %d out of bound!", idx);
        exit(1);
    }

    va_list ap;
    va_start(ap, idx);

    if (v->type == VEC_INT)
        ((int *)v->data)[idx] = va_arg(ap, int);

    if (v->type == VEC_FLOAT)
        ((float *)v->data)[idx] = (float)va_arg(ap, double);

    if (v->type == VEC_DOUBLE)
        ((double *)v->data)[idx] = va_arg(ap, double);

    if (v->type == VEC_CHAR)
        ((char *)v->data)[idx] = (char)va_arg(ap, int);

    if (v->type == VEC_VEC_P)
    {
        // Get the old vector
        vector_p old_v = (vector_p)get(v, idx);
        vector_p new_v = va_arg(ap, vector_p);

        // If both pointer points to the same vector
        if (old_v == new_v)
        {
            printf("WARNING: try to replace the vector with the same vector!");
            return;
        }

        if (old_v != NULL)
        {
            // Delete the old vector
            delete_vector(old_v);
        }

        // Assign the new pointer to the array
        ((vector_p *)v->data)[idx] = new_v;
    }

    va_end(ap);
}

// Add constant to a vector
const_op(+, add);

// Substract a constant from a vector
const_op(-, sub);

// Multiply constant to a vector
const_op(*, mul);

// Divide a vector by a constant
const_op(/, div);

// Format and print the vector
void print_vector_(vector_p v, unsigned char depth)
{
    printf("[");

    if (v->type == VEC_INT)
    {
        for (int i = 0; i < v->size; i++)
            printf("%i, ", as_int(get(v, i)));
    }

    if (v->type == VEC_FLOAT)
    {
        for (int i = 0; i < v->size; i++)
            printf("%.3f, ", as_float(get(v, i)));
    }

    if (v->type == VEC_DOUBLE)
    {
        for (int i = 0; i < v->size; i++)
            printf("%.3f, ", as_double(get(v, i)));
    }

    if (v->type == VEC_CHAR)
        printf("\"%s\"  ", ((char *)v->data));

    if (v->type == VEC_VEC_P)
    {
        if (depth <= 1)
            printf("<VEC_P>: %d  ", v->size);
        else
        {
            vector_p *vec_p_arr = (vector_p *)v->data;
            for (int i = 0; i < v->size; i++)
            {
                print_vector_(vec_p_arr[i], depth - 1);
                printf(", ");
            }
        }
    }

    if (v->size > 0 || (v->type == VEC_VEC_P && depth <= 1))
        printf("\b\b");

    printf("]");
}

// Resize the vector
void resize(vector_p v, int size)
{
    if (v->capacity >= size)
        return;

    while (v->capacity < size)
    {
        v->capacity *= 2;
    }

    if (v->type == VEC_INT)
        resize_realloc(v->data, int, v->capacity);

    if (v->type == VEC_FLOAT)
        resize_realloc(v->data, float, v->capacity);

    if (v->type == VEC_DOUBLE)
        resize_realloc(v->data, double, v->capacity);

    if (v->type == VEC_CHAR)
        resize_realloc(v->data, char, v->capacity);

    if (v->type == VEC_VEC_P)
        resize_realloc(v->data, vector_p, v->capacity);
}

// Push item to a vector
// float will be promoted to double
// char will be promoted to int
void push(vector_p v, ...)
{
    va_list ap;
    va_start(ap, v);

    resize(v, v->size + 1);

    if (v->type == VEC_INT)
        ((int *)v->data)[v->size] = va_arg(ap, int);

    // type promotion
    if (v->type == VEC_FLOAT)
        ((float *)v->data)[v->size] = (float)va_arg(ap, double);

    if (v->type == VEC_DOUBLE)
        ((double *)v->data)[v->size] = va_arg(ap, double);

    // type promotion
    if (v->type == VEC_CHAR)
        ((char *)v->data)[v->size] = (char)va_arg(ap, int);

    if (v->type == VEC_VEC_P)
        ((vector_p *)v->data)[v->size] = va_arg(ap, vector_p);

    va_end(ap);
    v->size += 1;
}

int main(int argc, char const *argv[])
{
    vector_p v = new_vector(VEC_VEC_P);

    push(v, new_vector(VEC_INT));
    push(get(v, 0), 2);
    push(get(v, 0), 1);
    push(get(v, 0), 'a');

    const_add(get(v, 0), 10);
    const_mul(get(v, 0), 2);

    push(v, new_vector(VEC_CHAR));
    push(get(v, 1), 'A');
    push(get(v, 1), 'B');
    push(get(v, 1), 'C');

    const_add(get(v, 1), 10);
    const_div(get(v, 1), 2);

    push(v, new_vector(VEC_FLOAT));
    push(get(v, 2), 1.0f);
    push(get(v, 2), 2.0f);

    const_add(get(v, 2), 10.0);
    const_sub(get(v, 2), 2.0);

    push(v, new_vector(VEC_DOUBLE));
    push(get(v, 3), 1.0);
    push(get(v, 3), 3.0);

    const_add(get(v, 3), 10.0);
    const_mul(get(v, 3), 2.0);

    resize(v, 100);

    print_vector(v, 3);
    delete_vector(v);

    return 0;
}
