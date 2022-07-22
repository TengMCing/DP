//
// Created by Patrick Li on 17/7/22.
//

#ifndef VEC_LANG_2_GENERIC_H
#define VEC_LANG_2_GENERIC_H

/*-----------------------------------------------------------------------------
 |  Include vector_p from "vector.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_VECTOR_H
//vector_p
#include "vector.h"
#endif//VEC_LANG_2_VECTOR_H

/*-----------------------------------------------------------------------------
 |  Include NUM_CLASS from "vector.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_CLASS_H
//NUM_CLASS
#include "class.h"
#endif//VEC_LANG_2_CLASS_H

/*-----------------------------------------------------------------------------
 |  Include const_args_p from "vector.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_ARGS_H
//args_p
#include "args.h"
#endif//VEC_LANG_2_ARGS_H

/*-----------------------------------------------------------------------------
 |  Class Information
 ----------------------------------------------------------------------------*/

#ifndef GENERIC_INFO

/// @description Generic information type.
typedef struct generic_info generic_info_t;

/// @description Generic information struct.
/// @details Generic requires the method takes (const_args_p) as input.
/// @param new_vector: (vector_p (*[NUM_CLASS])(const_args_p)). Array of pointers to new_vector method.
/// @param print_vector: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to print_vector method.
/// @param del_vector: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to del_vector method.
/// @param reserve: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to reserve method.
/// @param resize: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to resize method.
/// @param push: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to push method.
/// @param push_by_value: (void (*[NUM_CLASS])(const_args_p, va_list)). Array of pointers to push_by_value method.
/// @param pop: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to pop method.
/// @param insert: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to insert method.
/// @param insert_by_value: (void (*[NUM_CLASS])(const_args_p, va_list)). Array of pointers to insert by value method.
/// @param rm: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to rm method.
/// @param at: (void* (*[NUM_CLASS])(const_args_p)). Array of pointers to at method.
/// @param set: (void (*[NUM_CLASS])(const_args_p)). Array of pointers to set method.
/// @param set_by_value: (void (*[NUM_CLASS])(const_args_p, va_list)). Array of pointers to set by value method.

struct generic_info
{
    vector_p (*new_vector[NUM_CLASS])(const_args_p named_args);
    void (*print_vector[NUM_CLASS])(const_args_p named_args);
    void (*del_vector[NUM_CLASS])(const_args_p named_args);
    void (*reserve[NUM_CLASS])(const_args_p named_args);
    void (*resize[NUM_CLASS])(const_args_p named_args);
    void (*push[NUM_CLASS])(const_args_p named_args);
    void (*push_by_value[NUM_CLASS])(const_args_p named_args, va_list ap);
    void (*pop[NUM_CLASS])(const_args_p named_args);
    void (*insert[NUM_CLASS])(const_args_p named_args);
    void (*insert_by_value[NUM_CLASS])(const_args_p named_args, va_list ap);
    void (*rm[NUM_CLASS])(const_args_p named_args);
    void *(*at[NUM_CLASS])(const_args_p named_args);
    void (*set[NUM_CLASS])(const_args_p named_args);
    void (*set_by_value[NUM_CLASS])(const_args_p named_args, va_list ap);
};

/// @description Global variable for storing generic information.
generic_info_t GENERIC_INFO;

/// @description Initialize generic information.
/// @return No return.
void init_generic();
#endif//GENERIC_INFO

/*-----------------------------------------------------------------------------
 |  Vector Constructor
 ----------------------------------------------------------------------------*/

#ifndef new_vector

/// @description Generic of vector constructor.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .class : (VEC_CLASS). Class of the vector.
/// @named_arguments \b .type : (VEC_TYPE). Type of the vector.
/// @return (vector_p). A vector pointer.
vector_p new_vector_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of vector constructor. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .class : (VEC_CLASS). Class of the vector.
/// @named_arguments \b .type : (VEC_TYPE). Type of the vector.
/// @return (vector_p). A vector pointer.
#define new_vector(...) new_vector_(args(__VA_ARGS__))
#endif//new_vector

/*-----------------------------------------------------------------------------
 |  Vector Destroyer
 ----------------------------------------------------------------------------*/

#ifndef del_vector

/// @description Generic of vector destroyer.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .depth : (int). (optional). Layers of vectors to be deleted.
/// @return No return.
void del_vector_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of vector destroyer. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .depth : (int). (optional). Layers of vectors to be deleted.
/// @return No return.
#define del_vector(...) del_vector_(args(__VA_ARGS__))
#endif//del_vector

/*-----------------------------------------------------------------------------
 |  Vector Printer
 ----------------------------------------------------------------------------*/

#ifndef print_vector

/// @description Generic of vector printer.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @return No return.
void print_vector_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of vector printer. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @return No return.
#define print_vector(...) print_vector_(args(__VA_ARGS__))
#endif//print_vector

/*-----------------------------------------------------------------------------
 |  Reserve
 ----------------------------------------------------------------------------*/

#ifndef reserve

/// @description Generic of reserving memory for vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .capacity : (unsigned int). Target capacity.
/// @return No return.
void reserve_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of reserving memory for vector. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .capacity : (unsigned int). Target capacity.
/// @return No return.
#define reserve(...) reserve_(args(__VA_ARGS__))
#endif//reserve

/*-----------------------------------------------------------------------------
 |  Resize
 ----------------------------------------------------------------------------*/

#ifndef resize

/// @description Generic of resizing a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .size : (unsigned int). Target size.
/// @named_arguments \b .item_p : (void*). Void pointer to an initial value.
/// @return No return.
void resize_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of resizing a vector. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .size : (unsigned int). Target size.
/// @named_arguments \b .item_p : (void*). Void pointer to an initial value.
/// @return No return.
#define resize(...) resize_(args(__VA_ARGS__))
#endif//resize

/*-----------------------------------------------------------------------------
 |  Push
 ----------------------------------------------------------------------------*/

#ifndef push

/// @description Generic of pushing items to a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be pushed.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be pushed.
/// @return No return.
void push_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of pushing items to a vector. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be pushed.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be pushed.
/// @return No return.
#define push(...) push_(args(__VA_ARGS__))
#endif//push

/*-----------------------------------------------------------------------------
 |  Push By Value
 ----------------------------------------------------------------------------*/

#ifndef push_by_value

/// @description Generic of pushing items to a vector by value.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ...: Items to be pushed.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be pushed.
/// @return No return.
void push_by_value(const_args_p named_args, ...);
#endif//push_by_value

/*-----------------------------------------------------------------------------
 |  Pop
 ----------------------------------------------------------------------------*/

#ifndef pop

/// @description Generic of popping an item from a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @details If \b .index is not specified, \b .vector->size will be used.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). (optional). Index of the item.
/// @return No return.
void pop_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of popping items from a vector. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). (optional). Index of the item.
/// @return No return.
#define pop(...) pop_(args(__VA_ARGS__))
#endif//pop

/*-----------------------------------------------------------------------------
 |  Insert
 ----------------------------------------------------------------------------*/

#ifndef insert

/// @description Generic of inserting items into a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be inserted into.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be inserted.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be inserted.
/// @return No return.
void insert_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of inserting items into a vector. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be inserted into.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be inserted.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be inserted.
/// @return No return.
#define insert(...) insert_(args(__VA_ARGS__))
#endif//insert

/*-----------------------------------------------------------------------------
 |  Insert By Value
 ----------------------------------------------------------------------------*/

#ifndef insert_by_value

/// @description Generic of inserting items into a vector by value.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be inserted into.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be inserted.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be inserted.
/// @return No return.
void insert_by_value(const_args_p named_args, ...);
#endif//insert_by_value

/*-----------------------------------------------------------------------------
 |  Remove
 ----------------------------------------------------------------------------*/

#ifndef rm

/// @description Generic of removing items from a vector.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be removed.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be removed.
/// @return No return.
void rm_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of removing items from a vector. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .index : (unsigned int). Index of the item.
/// @return (return_val_t). A void pointer stored in \b return_val_t.item .
/// @return (void*). A void pointer to the item.
#define rm(...) rm_(args(__VA_ARGS__))
#endif//rm


/*-----------------------------------------------------------------------------
 |  At
 ----------------------------------------------------------------------------*/

#ifndef at

/// @description Generic of item getter.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .index : (unsigned int). Index of the item.
/// @return (void*). A void pointer to the item.
void *at_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of item getter. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to the vector.
/// @named_arguments \b .index : (unsigned int). Index of the item.
/// @return (return_val_t). A void pointer stored in \b return_val_t.item .
/// @return (void*). A void pointer to the item.
#define at(...) at_(args(__VA_ARGS__))
#endif//at

/*-----------------------------------------------------------------------------
 |  Set
 ----------------------------------------------------------------------------*/

#ifndef set

/// @description Generic of item setter.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be assigned to.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be assigned.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be assigned.
/// @return No return.
void set_(const_args_p named_args);

/// @description Macro to specify named arguments for the generic of item setter. \n
/// Provide named arguments as .arg_name = arg_val.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be assigned to.
/// @named_arguments \b .item_p : (void*). Void pointer to items to be assigned.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be assigned.
/// @return No return.
#define set(...) set_(args(__VA_ARGS__))
#endif//set

/*-----------------------------------------------------------------------------
 |  Set By Value
 ----------------------------------------------------------------------------*/

#ifndef set_by_value

/// @description Generic of item setter by value.
/// @param named_args: (const_args_p). Pointer to named arguments.
/// @param ...: Items to be assigned.
/// @named_arguments \b .vector : (vector_p). Pointer to a vector.
/// @named_arguments \b .index : (unsigned int). Index of the first item to be assigned to.
/// @named_arguments \b .num_item : (unsigned int). Number of items to be assigned.
/// @return No return.
void set_by_value(const_args_p named_args, ...);
#endif//set_by_value


#endif//VEC_LANG_2_GENERIC_H
