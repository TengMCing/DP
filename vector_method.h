//
// Created by Patrick Li on 17/7/22.
//

#ifndef VEC_LANG_2_VECTOR_METHOD_H
#define VEC_LANG_2_VECTOR_METHOD_H

/*-----------------------------------------------------------------------------
 |  Include va_list from <stdarg.h>
 ----------------------------------------------------------------------------*/

#include <stdarg.h>

/*-----------------------------------------------------------------------------
 |  Include vector_p, VEC_TYPE from "vector.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_VECTOR_H
//vector_p, VEC_TYPE
#include "vector.h"
#endif//VEC_LANG_2_VECTOR_H

/*-----------------------------------------------------------------------------
 |  Include const_args_p from "vector.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_ARGS_H
//const_args_p
#include "args.h"
#endif//VEC_LANG_2_ARGS_H

/*-----------------------------------------------------------------------------
 |  Vector Constructor: VECTOR_new_vector
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_new_vector

/// @description Vector constructor.
/// @param type: (VEC_TYPE). Type of the vector.
/// @return (vector_p). Pointer to the new vector.
vector_p VECTOR_new_vector(VEC_TYPE type);

/// @description Caller of vector constructor.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .type : (VEC_TYPE). Type of the vector.
/// @return (vector_p). Pointer to the new vector.
vector_p caller_VECTOR_new_vector(const_args_p named_args);
#endif//VECTOR_new_vector

/*-----------------------------------------------------------------------------
 |  Vector Destroyer: VECTOR_new_vector
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_del_vector

/// @description Vector destroyer.
/// @details Function will return if \b depth smaller than 1.
/// @param vector: (vector_p). Pointer to a vector.
/// @param depth: (int). Layers of vectors to be deleted.
/// @return No return.
void VECTOR_del_vector(vector_p vector, int depth);

/// @description Caller of vector destroyer.
/// @details Function will return if \b .depth smaller than 1. If \b .depth
/// is not specified, 1 will be used.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .depth : (int). (optional). Layers of vectors to be deleted.
/// @return No return.
void caller_VECTOR_del_vector(const_args_p named_args);
#endif//VECTOR_del_vector

/*-----------------------------------------------------------------------------
 |  Vector Printer: VECTOR_print_vector
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_print_vector

/// @description Vector (VEC_VEC_P) printer.
/// @param vector: (vector_p). Pointer to a vector.
/// @param depth: (int). Layers of vectors to be expanded in the output.
/// @return No return.
void VECTOR_print_vector_(vector_p vector, int depth);

#define VECTOR_print_vector(vector, depth)   \
    {                                        \
        VECTOR_print_vector_(vector, depth); \
        printf("\n");                        \
    }

/// @description Caller of vector printer.
/// @details If \b .depth is not specified, 1 will be used.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .depth : (int). (optional). Layers of vectors to be expanded in the output.
/// @return No return.
void caller_VECTOR_print_vector(const_args_p named_args);
#endif//VECTOR_print_vector

/*-----------------------------------------------------------------------------
 |  Reserve: VECTOR_reserve
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_reserve

/// @description Reserve memory for a vector.
/// @details Function will return if the target \b capacity is smaller or equal to the current capacity.
/// @param vector: (vector_p). Pointer to a vector.
/// @param capacity: (unsigned int). Target capacity of the vector.
/// @return No return.
void VECTOR_reserve(vector_p vector, unsigned int capacity);

/// @description Reserve memory for a vector.
/// @details Function will return if the target \b capacity is smaller or equal to the current capacity.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .capacity : (unsigned int). Target capacity of the vector.
/// @return No return.
void caller_VECTOR_reserve(const_args_p named_args);
#endif//VECTOR_reserve

/*-----------------------------------------------------------------------------
 |  Resize: VECTOR_resize
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_resize

/// @description Resize a vector.
/// @details If the target \b size is smaller then the current size, items at the end will be removed. \n
/// If the target \b size is larger than the current size, vector will be extend and items will be initialized with \b init_value. \n
/// If the target \b size is larger than the current capacity, additional memory will be required.
/// @param vector: (vector_p). Pointer to a vector.
/// @param size: (unsigned int). Target size of the vector.
/// @param item_p: (void*). Void pointer to an initial value.
/// @return No return.
void VECTOR_resize(vector_p vector, unsigned int size, void *item_p);

/// @description Resize a vector.
/// @details If the target \b size is smaller then the current size, items at the end will be removed. \n
/// If the target \b size is larger than the current size, vector will be extend and items will be initialized with \b init_value. \n
/// If the target \b size is larger than the current capacity, additional memory will be required.
/// If \b .item_p is not specified, NULL will be used.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .size : (unsigned int). Target size of the vector.
/// @named_arguments \b item_p : (void*). (optional). Void pointer to an initial value.
/// @return No return.
void caller_VECTOR_resize(const_args_p named_args);
#endif//VECTOR_resize

/*-----------------------------------------------------------------------------
 |  Push: VECTOR_push
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_push

/// @description Push items to the end of a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param item_p: (void*). Void pointer to items to be pushed.
/// @param num_item: (unsigned int). Number of items to be pushed.
/// @return No return.
void VECTOR_push(vector_p vector, void *item_p, unsigned int num_item);

/// @description Push items to the end of a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @details If \b .num_item is not specified, 1 will be used.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be pushed.
/// @named_arguments \b .num_item : (unsigned int). (optional). Number of items to be pushed.
/// @return No return.
void caller_VECTOR_push(const_args_p named_args);

/// @description Macro to push items to a vector without any checks.
#define VECTOR_fast_push(vector, item_p, num_item)                 \
    {                                                              \
        VECTOR_reserve(vector, (vector)->size + (num_item));       \
        VECTOR_fast_set(vector, (vector)->size, item_p, num_item); \
        (vector)->size += (num_item);                              \
    }
#endif//VECTOR_push

/*-----------------------------------------------------------------------------
 |  Push By Value: VECTOR_push_by_value
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_push_by_value

/// @description Push items to the end of a vector.
/// @details (char) will be promoted to (int) and (float) will be promoted to (double).
/// @param vector: (vector_p). Pointer to a vector.
/// @param num_item: (unsigned int). Number of items to be pushed.
/// @param ap: (va_list) Items to be pushed passed by a variadic function.
/// @return No return.
void VECTOR_push_by_value(vector_p vector, unsigned int num_item, va_list ap);

/// @description Push items to the end of a vector.
/// @details Since this is a variadic function, (char) will be promoted to (int) and (float) will be promoted to (double).
/// @param vector: (vector_p). Pointer to a vector.
/// @param num_item: (unsigned int). Number of items to be pushed.
/// @param ...: Items to be pushed.
/// @return No return.
void VECTOR_push_by_value_variadic(vector_p vector, unsigned int num_item, ...);

/// @description Push items to the end of a vector.
/// @details (char) will be promoted to (int) and (float) will be promoted to (double).
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ap: (va_list). Items to be pushed passed by a variadic function.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be pushed.
/// @return No return.
void caller_VECTOR_push_by_value(const_args_p named_args, va_list ap);

/// @description Push items to the end of a vector.
/// @details Since this is a variadic function, (char) will be promoted to (int) and (float) will be promoted to (double).
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ...: Items to be pushed.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be pushed.
/// @return No return.
void caller_VECTOR_push_by_value_variadic(const_args_p named_args, ...);
#endif//VECTOR_push_by_value

/*-----------------------------------------------------------------------------
 |  Pop: VECTOR_pop
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_pop

/// @description Pop an item from a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the item.
/// @return No return.
void VECTOR_pop(vector_p vector, unsigned int index);

/// @description Pop an item from a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @details If \b .index is not specified, \b .vector->size will be used.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). (optional). Index of the item.
/// @return No return.
void caller_VECTOR_pop(const_args_p named_args);
#endif//VECTOR_pop

/*-----------------------------------------------------------------------------
 |  Insert: VECTOR_insert
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_insert

/// @description Insert items into a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the first item to be inserted into.
/// @param item_p: (void*). Void pointer to items to be inserted.
/// @param num_item: (unsigned int). Number of items to be inserted.
/// @return No return.
void VECTOR_insert(vector_p vector, unsigned int index, void *item_p, unsigned int num_item);

/// @description Insert items into a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be inserted into.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be inserted.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be inserted.
/// @return No return.
void caller_VECTOR_insert(const_args_p named_args);

#define VECTOR_fast_insert(vector, index, item_p, num_item)                                         \
    {                                                                                               \
        VECTOR_reserve(vector, (vector)->size + (num_item));                                        \
        (vector)->size += (num_item);                                                               \
        VECTOR_fast_set(vector, (index) + (num_item), VECTOR_fast_at_raw(vector, index), num_item); \
        VECTOR_fast_set(vector, index, item_p, num_item);                                           \
    }
#endif//VECTOR_insert

/*-----------------------------------------------------------------------------
 |  Insert By Value: VECTOR_insert_by_value
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_insert_by_value

/// @description Insert items into a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the first item to be inserted into.
/// @param num_item: (unsigned int). Number of items to be inserted.
/// @param ap: (va_list) Items to be inserted passed by a variadic function.
/// @return No return.
void VECTOR_insert_by_value(vector_p vector, unsigned int index, unsigned int num_item, va_list ap);

/// @description Insert items into a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the first item to be inserted into.
/// @param num_item: (unsigned int). Number of items to be inserted.
/// @param ...: Items to be inserted.
/// @return No return.
void VECTOR_insert_by_value_variadic(vector_p vector, unsigned int index, unsigned int num_item, ...);

/// @description Insert items into a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ap: (va_list) Items to be inserted passed by a variadic function.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be inserted into.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be inserted.
/// @return No return.
void caller_VECTOR_insert_by_value(const_args_p named_args, va_list ap);

/// @description Insert items into a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ...: Items to be inserted.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be inserted into.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be inserted.
/// @return No return.
void caller_VECTOR_insert_by_value_variadic(const_args_p named_args, ...);
#endif//VECTOR_insert_by_value

/*-----------------------------------------------------------------------------
 |  Remove: VECTOR_rm
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_rm

/// @description Remove items from a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the first item to be removed.
/// @param num_item: (unsigned int). Number of items to be removed.
/// @return No return.
void VECTOR_rm(vector_p vector, unsigned int index, unsigned int num_item);

/// @description Remove items from a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be removed.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be removed.
/// @return No return.
void caller_VECTOR_rm(const_args_p named_args);

#define VECTOR_fast_rm(vector, index, num_item)                                                                                      \
    {                                                                                                                                \
        if ((vector)->size - (index) - (num_item) > 0)                                                                               \
            VECTOR_fast_set(vector, index, VECTOR_fast_at_raw(vector, (index) + (num_item)), (vector)->size - (index) - (num_item)); \
        (vector)->size -= (num_item);                                                                                                \
    }
#endif//VECTOR_rm

/*-----------------------------------------------------------------------------
 |  At: VECTOR_at
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_at

/// @description Get an item from a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the item.
/// @return (void*). Void pointer to the item.
void *VECTOR_at(vector_p vector, unsigned int index);

/// @description Get an item from a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the item.
/// @return (void*). Void pointer to the item.
void *caller_VECTOR_at(const_args_p named_args);

/// @description Macro to get an item from a vector without any checks.
#define VECTOR_fast_at_raw(vector, index) (((unsigned char *) (vector)->data_p) + (index) *vec_sizeof((vector)->type))
#endif//VECTOR_at

/*-----------------------------------------------------------------------------
 |  Set: VECTOR_set
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_set

/// @description Set values for a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the first item to be assigned to.
/// @param item_p: (void*). Void pointer to items to be assigned.
/// @param num_item: (unsigned int). Number of items to be assigned.
/// @return No return.
void VECTOR_set(vector_p vector, unsigned int index, void *item_p, unsigned int num_item);

/// @description Set values for a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be assigned to.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be assigned.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be assigned.
/// @return No return.
void caller_VECTOR_set(const_args_p named_args);

#define VECTOR_fast_set(vector, index, item_p, num_item) memmove(VECTOR_fast_at_raw(vector, index), item_p, (num_item) *vec_sizeof((vector)->type))
#endif//VECTOR_set

/*-----------------------------------------------------------------------------
 |  Set By Value: VECTOR_insert_by_value
 ----------------------------------------------------------------------------*/

#ifndef VECTOR_set_by_value

/// @description Set values for a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the first item to be assigned to.
/// @param num_item: (unsigned int). Number of items to be assigned.
/// @param ap: (va_list) Items to be inserted passed by a variadic function.
/// @return No return.
void VECTOR_set_by_value(vector_p vector, unsigned int index, unsigned int num_item, va_list ap);

/// @description Set values for a vector.
/// @param vector: (vector_p). Pointer to a vector.
/// @param index: (unsigned int). Index of the first item to be assigned to.
/// @param num_item: (unsigned int). Number of items to be assigned.
/// @param ...: Items to be assigned.
/// @return No return.
void VECTOR_set_by_value_variadic(vector_p vector, unsigned int index, unsigned int num_item, ...);

/// @description Set values for a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ap: (va_list) Items to be inserted passed by a variadic function.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be assigned to.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be assigned.
/// @return No return.
void caller_VECTOR_set_by_value(const_args_p named_args, va_list ap);

/// @description Set values for a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ...: Items to be assigned.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be assigned to.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be assigned.
/// @return No return.
void caller_VECTOR_set_by_value_variadic(const_args_p named_args, ...);
#endif//VECTOR_set_by_value

#endif//VEC_LANG_2_VECTOR_METHOD_H
