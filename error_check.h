//
// Created by Patrick Li on 16/7/22.
//

#ifndef VEC_LANG_2_ERROR_CHECK_H
#define VEC_LANG_2_ERROR_CHECK_H

/*-----------------------------------------------------------------------------
|  Check Vector Type
-----------------------------------------------------------------------------*/

#ifndef check_type

/// @description Macro to check the vector type.
#define check_type(type)                        \
    if ((type) > VEC_VEC_P || (type) < VEC_INT) \
        UndefinedTypeError(type);
#endif//check_type

/*-----------------------------------------------------------------------------
 |  Check Vector Class
 ----------------------------------------------------------------------------*/

#ifndef check_class

/// @description Macro to check the vector type.
#define check_class(class)                                             \
    if ((class) > VECTOR || (class) < VECTOR || (class) == NULL_CLASS) \
        UndefinedClassError(class);
#endif//check_class

/*-----------------------------------------------------------------------------
 |  Check Index Out of Bound
 ----------------------------------------------------------------------------*/

#ifndef check_index_out_of_bound

/// @description Macro to check the index.
#define check_index_out_of_bound(vector, index)   \
    if ((index) < 0 || (index) >= (vector)->size) \
        IndexOutOfBoundError(index);
#endif//check_index_out_of_bound

/*-----------------------------------------------------------------------------
 |  Check Number Of Items
 ----------------------------------------------------------------------------*/

#ifndef check_zero_item

/// @description Macro to check the number of items.
#define check_zero_item(num_item) \
    if ((num_item) < 1)           \
        ZeroItemError(num_item);
#endif//check_zero_item

/*-----------------------------------------------------------------------------
 |  Check VEC_VEC_P Vector Type
 ----------------------------------------------------------------------------*/

#ifndef check_vec_vec_p

/// @description Macro to check the VEC_VEC_P vector type.
#define check_vec_vec_p(type) \
    if ((type) != VEC_VEC_P)  \
        NotVECPError(type);
#endif//check_vec_vec_p

/*-----------------------------------------------------------------------------
 |  Check missing argument
 ----------------------------------------------------------------------------*/

#ifndef check_missing_argument

/// @description Macro to check the missing argument.
#define check_missing_argument(named_args, arg_name) \
    if (missing_##arg_name(named_args->arg_name))    \
        MissingArgumentError(#arg_name);
#endif//check_missing_argument

#endif//VEC_LANG_2_ERROR_CHECK_H
