#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-misplaced-const"
//
// Created by Patrick Li on 17/7/22.
//

#include "vector_method.h"
#include "error.h"
#include "error_check.h"
#include "utilities.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------
 |  Static Macros to call function with variadic list
 ----------------------------------------------------------------------------*/

#define collect_ap_as_item_p(type, promotion, num_item) \
    type item_p[num_item];                              \
    for (unsigned int i = 0; i < (num_item); i++)       \
        item_p[i] = (type) va_arg(ap, promotion);


#define call_with_ap_as_item_p(type, ap, num_item, call)        \
    {                                                           \
        switch (type)                                           \
        {                                                       \
        case VEC_INT:                                           \
        {                                                       \
            collect_ap_as_item_p(int, int, num_item);           \
            call;                                               \
            break;                                              \
        }                                                       \
        case VEC_LONG:                                          \
        {                                                       \
            collect_ap_as_item_p(long, long, num_item);         \
            call;                                               \
            break;                                              \
        }                                                       \
        case VEC_FLOAT:                                         \
        {                                                       \
            collect_ap_as_item_p(float, double, num_item);      \
            call;                                               \
            break;                                              \
        }                                                       \
        case VEC_DOUBLE:                                        \
        {                                                       \
            collect_ap_as_item_p(double, double, num_item);     \
            call;                                               \
            break;                                              \
        }                                                       \
        case VEC_CHAR:                                          \
        {                                                       \
            collect_ap_as_item_p(char, int, num_item);          \
            call;                                               \
            break;                                              \
        }                                                       \
        case VEC_VEC_P:                                         \
        {                                                       \
            collect_ap_as_item_p(vector_p, vector_p, num_item); \
            call;                                               \
            break;                                              \
        }                                                       \
        default:                                                \
            UndefinedTypeError(type);                           \
        }                                                       \
    }

/*-----------------------------------------------------------------------------
 |  Vector Constructor: VECTOR_new_vector
 ----------------------------------------------------------------------------*/

vector_p VECTOR_new_vector(const VEC_TYPE type)
{
    check_type(type);

    // Allocate memory for the struct
    vector_p vector = malloc(sizeof(vector_t));
    vector->capacity = DEFAULT_VEC_CAPACITY;
    vector->size = 0;
    vector->type = type;
    vector->class = VECTOR;
    // TODO: Implement runtime reference counting
    vector->id = 0;

    for (int i = 0; i < MAX_VEC_NAME_LEN; i++)
        vector->name[i] = '\0';

    // Allocate memory for the container
    vector->data_p = calloc(vector->capacity, vec_sizeof(type));

    return vector;
}

vector_p caller_VECTOR_new_vector(const_args_p const named_args)
{
    check_missing_argument(named_args, type);
    return VECTOR_new_vector(named_args->type);
}

/*-----------------------------------------------------------------------------
 |  Vector Destroyer: VECTOR_new_vector
 ----------------------------------------------------------------------------*/

void VECTOR_del_vector(vector_p const vector, const int depth)
{
    check_type(vector->type);

    if (depth < 1)
        return;

    if (vector->type == VEC_VEC_P)
    {
        for (unsigned int i = 0; i < vector->size; i++)
            VECTOR_del_vector(VECTOR_at(vector, i), depth - 1);
    }

    // Deallocate memory for the container
    free(vector->data_p);

    // Deallocate memory for the struct
    free(vector);
}

void caller_VECTOR_del_vector(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    if (missing_depth(named_args->depth))
        VECTOR_del_vector(named_args->vector, 1);
    else
        VECTOR_del_vector(named_args->vector, named_args->depth);
}


/*-----------------------------------------------------------------------------
 |  Vector Printer: VECTOR_print_vector
 ----------------------------------------------------------------------------*/

void VECTOR_print_vector_(vector_p const vector, const int depth)
{
    printf("[");

    switch (vector->type)
    {
    case VEC_INT:
        for (unsigned int i = 0; i < vector->size; i++)
            printf("%i, ", as_int(VECTOR_at(vector, i)));
        break;
    case VEC_LONG:
        for (unsigned int i = 0; i < vector->size; i++)
            printf("%li, ", as_long(VECTOR_at(vector, i)));
        break;
    case VEC_FLOAT:
        for (unsigned int i = 0; i < vector->size; i++)
            printf("%.3f, ", as_float(VECTOR_at(vector, i)));
        break;
    case VEC_DOUBLE:
        for (unsigned int i = 0; i < vector->size; i++)
            printf("%.3f, ", as_double(VECTOR_at(vector, i)));
        break;
    case VEC_CHAR:
        printf("\"%s\"  ", as_string(vector->data_p));
        break;
    case VEC_VEC_P:
        if (depth <= 1)
            printf("<VEC_P>: %d  ", vector->size);
        else
            for (unsigned int i = 0; i < vector->size; i++)
            {
                VECTOR_print_vector_(VECTOR_at(vector, i), depth - 1);
                printf(", ");
            }
        break;
    default:
        UndefinedTypeError(vector->type);
    }

    if (vector->size > 0 ||
        (vector->type == VEC_VEC_P && depth <= 1) ||
        (vector->type == VEC_CHAR && vector->size == 0))
        printf("\b\b");

    printf("]");
}

void caller_VECTOR_print_vector(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    if (missing_depth(named_args->depth))
    {
        VECTOR_print_vector(named_args->vector, 1);
        return;
    }
    VECTOR_print_vector(named_args->vector, named_args->depth);
}

/*-----------------------------------------------------------------------------
 |  Reserve: VECTOR_reserve
 ----------------------------------------------------------------------------*/

void VECTOR_reserve(vector_p const vector, const unsigned int capacity)
{
    check_type(vector->type);

    if (vector->capacity >= capacity)
        return;

    while (vector->capacity < capacity)
        vector->capacity = vector->capacity * 2 + 8;

    vector->data_p = realloc(vector->data_p, vec_sizeof(vector->type) * vector->capacity);
}

void caller_VECTOR_reserve(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, capacity);
    VECTOR_reserve(named_args->vector, named_args->capacity);
}

/*-----------------------------------------------------------------------------
 |  Resize: VECTOR_resize
 ----------------------------------------------------------------------------*/

void VECTOR_resize(vector_p const vector, const unsigned int size, void *const item_p)
{
    if (size == vector->size)
        return;

    if (size < 0)
        IndexOutOfBoundError(size);

    if (size > vector->size)
    {
        check_type((vector)->type);
        VECTOR_reserve(vector, size);
        for (unsigned int i = 0; i < size - vector->size; i++)
            VECTOR_fast_push(vector, item_p, 1);
        return;
    }

    if (size < vector->size)
        vector->size = size;
}

void caller_VECTOR_resize(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, size);
    if (missing_item_p(named_args->item_p))
        VECTOR_resize(named_args->vector, named_args->size, NULL);
    else
        VECTOR_resize(named_args->vector, named_args->size, named_args->item_p);
}

/*-----------------------------------------------------------------------------
 |  Push: VECTOR_push
 ----------------------------------------------------------------------------*/

void VECTOR_push(vector_p const vector, void *const item_p, const unsigned int num_item)
{
    check_zero_item(num_item);
    check_type((vector)->type);
    VECTOR_fast_push(vector, item_p, num_item);
}

void caller_VECTOR_push(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, item_p);
    check_missing_argument(named_args, num_item);

    if (missing_num_item(named_args->num_item))
        VECTOR_push(named_args->vector, named_args->item_p, 1);
    else
        VECTOR_push(named_args->vector, named_args->item_p, named_args->num_item);
}

/*-----------------------------------------------------------------------------
 |  Push By Value: VECTOR_push_by_value
 ----------------------------------------------------------------------------*/

void VECTOR_push_by_value(vector_p const vector, const unsigned int num_item, va_list ap)
{
    check_zero_item(num_item);
    check_type(vector->type);
    call_with_ap_as_item_p(vector->type,
                           ap,
                           num_item,
                           VECTOR_fast_push(vector, item_p, num_item));
}

void caller_VECTOR_push_by_value(const_args_p const named_args, va_list ap)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, num_item);
    VECTOR_push_by_value(named_args->vector, named_args->num_item, ap);
}

void VECTOR_push_by_value_variadic(vector_p const vector, const unsigned int num_item, ...)
{
    va_list ap;
    va_start(ap, num_item);
    VECTOR_push_by_value(vector, num_item, ap);
    va_end(ap);
}

void caller_VECTOR_push_by_value_variadic(const_args_p const named_args, ...)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, num_item);
    va_list ap;
    va_start(ap, named_args);
    VECTOR_push_by_value(named_args->vector, named_args->num_item, ap);
    va_end(ap);
}

/*-----------------------------------------------------------------------------
 |  Pop: VECTOR_pop
 ----------------------------------------------------------------------------*/

void VECTOR_pop(vector_p const vector, const unsigned int index)
{
    check_type(vector->type);
    check_index_out_of_bound(vector, index);
    VECTOR_fast_rm(vector, index, 1);
}

void caller_VECTOR_pop(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    if (missing_index(named_args->index))
        VECTOR_pop(named_args->vector, named_args->vector->size - 1);
    else
        VECTOR_pop(named_args->vector, named_args->index);
}

/*-----------------------------------------------------------------------------
 |  Insert: VECTOR_insert
 ----------------------------------------------------------------------------*/

void VECTOR_insert(vector_p const vector, const unsigned int index, void *item_p, const unsigned int num_item)
{
    check_index_out_of_bound(vector, index);
    check_zero_item(num_item);
    check_type(vector->type);
    VECTOR_fast_insert(vector, index, item_p, num_item);
}

void caller_VECTOR_insert(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    check_missing_argument(named_args, item_p);
    if (missing_num_item(named_args->num_item))
        VECTOR_insert(named_args->vector, named_args->index, named_args->item_p, 1);
    else
        VECTOR_insert(named_args->vector, named_args->index, named_args->item_p, named_args->num_item);
}

/*-----------------------------------------------------------------------------
 |  Insert By Value: VECTOR_insert_by_value
 ----------------------------------------------------------------------------*/

void VECTOR_insert_by_value(vector_p vector, unsigned int index, unsigned int num_item, va_list ap)
{
    check_index_out_of_bound(vector, index);
    check_zero_item(num_item);
    check_type(vector->type);
    call_with_ap_as_item_p(vector->type,
                           ap,
                           num_item,
                           VECTOR_fast_insert(vector, index, item_p, num_item));
}

void VECTOR_insert_by_value_variadic(vector_p vector, unsigned int index, unsigned int num_item, ...)
{
    va_list ap;
    va_start(ap, num_item);
    VECTOR_insert_by_value(vector, index, num_item, ap);
    va_end(ap);
}

void caller_VECTOR_insert_by_value(const_args_p named_args, va_list ap)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    if (missing_num_item(named_args->num_item))
        VECTOR_insert_by_value(named_args->vector, named_args->index, 1, ap);
    else
        VECTOR_insert_by_value(named_args->vector, named_args->index, named_args->num_item, ap);
}

void caller_VECTOR_insert_by_value_variadic(const_args_p named_args, ...)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    va_list ap;
    va_start(ap, named_args);
    if (missing_num_item(named_args->num_item))
        VECTOR_insert_by_value(named_args->vector, named_args->index, 1, ap);
    else
        VECTOR_insert_by_value(named_args->vector, named_args->index, named_args->num_item, ap);
    va_end(ap);
}

/*-----------------------------------------------------------------------------
 |  Remove: VECTOR_rm
 ----------------------------------------------------------------------------*/

void VECTOR_rm(vector_p vector, unsigned int index, unsigned int num_item)
{
    check_index_out_of_bound(vector, index);
    check_zero_item(num_item);
    if ((index) + (num_item) -1 >= (vector)->size)
        IndexOutOfBoundError((index) + (num_item) -1);
    VECTOR_fast_rm(vector, index, num_item);
}

void caller_VECTOR_rm(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    if (missing_num_item(named_args->num_item))
        VECTOR_rm(named_args->vector, named_args->index, 1);
    else
        VECTOR_rm(named_args->vector, named_args->index, named_args->num_item);
}

/*-----------------------------------------------------------------------------
 |  At: VECTOR_at
 ----------------------------------------------------------------------------*/

void *VECTOR_at(vector_p const vector, const unsigned int index)
{
    check_index_out_of_bound(vector, index);
    if (vector->type == VEC_VEC_P)
        return *(vector_p *) (((unsigned char *) vector->data_p) + index * vec_sizeof(vector->type));
    return VECTOR_fast_at_raw(vector, index);
}

void *caller_VECTOR_at(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    return VECTOR_at(named_args->vector, named_args->index);
}

/*-----------------------------------------------------------------------------
 |  Set: VECTOR_set
 ----------------------------------------------------------------------------*/

void VECTOR_set(vector_p const vector, const unsigned int index, void *item_p, const unsigned int num_item)
{
    check_type(vector->type);
    check_index_out_of_bound(vector, index);
    check_zero_item(num_item);
    if (index + num_item - 1 >= vector->size)
        IndexOutOfBoundError(index + num_item - 1);
    VECTOR_fast_set(vector, index, item_p, num_item);
}

void caller_VECTOR_set(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    check_missing_argument(named_args, item_p);
    if (missing_num_item(named_args->num_item))
        VECTOR_set(named_args->vector, named_args->index, named_args->item_p, 1);
    else
        VECTOR_set(named_args->vector, named_args->index, named_args->item_p, named_args->num_item);
}

/*-----------------------------------------------------------------------------
 |  Set By Value: VECTOR_insert_by_value
 ----------------------------------------------------------------------------*/

void VECTOR_set_by_value(vector_p vector, unsigned int index, unsigned int num_item, va_list ap)
{
    check_index_out_of_bound(vector, index);
    check_zero_item(num_item);
    check_type(vector->type);
    if (index + num_item - 1 >= vector->size)
        IndexOutOfBoundError(index + num_item - 1);
    call_with_ap_as_item_p(vector->type, ap, num_item, VECTOR_fast_set(vector, index, item_p, num_item));
}

void VECTOR_set_by_value_variadic(vector_p vector, unsigned int index, unsigned int num_item, ...)
{
    va_list ap;
    va_start(ap, num_item);
    VECTOR_set_by_value(vector, index, num_item, ap);
    va_end(ap);
}

void caller_VECTOR_set_by_value(const_args_p named_args, va_list ap)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    check_missing_argument(named_args, num_item);
    VECTOR_set_by_value(named_args->vector, named_args->index, named_args->num_item, ap);
}

void caller_VECTOR_set_by_value_variadic(const_args_p named_args, ...)
{
    check_missing_argument(named_args, vector);
    check_missing_argument(named_args, index);
    check_missing_argument(named_args, num_item);
    va_list ap;
    va_start(ap, named_args);
    VECTOR_set_by_value(named_args->vector, named_args->index, named_args->num_item, ap);
    va_end(ap);
}

#undef collect_ap_as_item_p
#undef call_with_ap_as_item_p

#pragma clang diagnostic pop