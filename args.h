//
// Created by Patrick Li on 16/7/22.
//

#ifndef VEC_LANG_2_ARGS_H
#define VEC_LANG_2_ARGS_H

/*-----------------------------------------------------------------------------
 |  Include va_list from "vector.h"
 ----------------------------------------------------------------------------*/

//va_list
#include <stdarg.h>

/*-----------------------------------------------------------------------------
 |  Include INT_MIN, UINT_MAX from "vector.h"
 ----------------------------------------------------------------------------*/

//INT_MIN, UNIT_MAX
#include <limits.h>

/*-----------------------------------------------------------------------------
 |  Include VEC_TYPE, NULL from "vector.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_VECTOR_H
//VEC_TYPE, NULL
#include "vector.h"
#endif//VEC_LANG_2_VECTOR_H

/*-----------------------------------------------------------------------------
 |  Include VEC_CLASS from "class.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_CLASS_H
//VEC_CLASS
#include "class.h"
#endif//VEC_LANG_2_CLASS_H

/*-----------------------------------------------------------------------------
 |  Named Arguments
 ----------------------------------------------------------------------------*/

#ifndef args

/// @description Named argument type.
typedef struct args args_t;

/// @description Pointer to constant named arguments.
typedef const args_t *const_args_p;

/// @description Named argument struct. Check the corresponding function for the meanings of the named arguments.
/// @param class: (VEC_CLASS).
/// @param type: (VEC_TYPE).
/// @param vector: (vector_p).
/// @param depth: (int).
/// @param index: (unsigned int).
/// @param capacity: (unsigned int).
/// @param size: (unsigned int).
/// @param item_p: (void*)
struct args
{
    VEC_CLASS class;
    VEC_TYPE type;
    vector_p vector;
    int depth;
    unsigned int index;
    unsigned int capacity;
    unsigned int size;
    void *item_p;
    unsigned int num_item;
};

/// @description Macro for default named arguments.
#define default_args .class = NULL_CLASS,  \
                     .type = VEC_NULL,     \
                     .vector = NULL,       \
                     .depth = INT_MIN,     \
                     .index = UINT_MAX,    \
                     .capacity = UINT_MAX, \
                     .size = UINT_MAX,     \
                     .item_p = NULL,       \
                     .num_item = UINT_MAX

/// @description Macro to check if class is specified.
#define missing_class(class) class == NULL_CLASS

/// @description Macro to check if type is specified.
#define missing_type(type) type == VEC_NULL

/// @description Macro to check if vector is specified.
#define missing_vector(vector) vector == NULL

/// @description Macro to check if depth is specified.
#define missing_depth(depth) ((depth) == -32768)

/// @description Macro to check if index is specified.
#define missing_index(index) index == UINT_MAX

/// @description Macro to check if capacity is specified.
#define missing_capacity(capacity) capacity == UINT_MAX

/// @description Macro to check if size is specified.
#define missing_size(size) size == UINT_MAX

/// @description Macro to check if item_p is specified.
#define missing_item_p(item_p) item_p == NULL

/// @description Macro to check if num_item is specified.
#define missing_num_item(num_item) num_item == UINT_MAX

/// @description Macro to initialize an args_t and return its address.
#define args(...) \
    ({ const args_t input_args = {default_args, __VA_ARGS__}; &input_args; })
#endif//args

/*-----------------------------------------------------------------------------
 |  Return value
 ----------------------------------------------------------------------------*/

// #ifndef return_val
//
// /// @description Returned value type.
// typedef union return_val return_val_t;
//
// /// @description Returned value union.
// /// @param vector: (vector_p). Vector pointer.
// /// @param item: (void*). Void pointer to item.
// union return_val
// {
//     vector_p vector;
//     void *item;
// };
// #endif//return_val

#endif//VEC_LANG_2_ARGS_H
