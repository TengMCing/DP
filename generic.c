//
// Created by Patrick Li on 17/7/22.
//

#include "generic.h"
#include "error.h"
#include "error_check.h"
#include "vector_method.h"
#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------
 |  Initialize Generic Info
 ----------------------------------------------------------------------------*/

void init_generic()
{
    GENERIC_INFO.new_vector[VECTOR] = &caller_VECTOR_new_vector;
    GENERIC_INFO.print_vector[VECTOR] = &caller_VECTOR_print_vector;
    GENERIC_INFO.del_vector[VECTOR] = &caller_VECTOR_del_vector;
    GENERIC_INFO.at[VECTOR] = &caller_VECTOR_at;
    GENERIC_INFO.reserve[VECTOR] = &caller_VECTOR_reserve;
    GENERIC_INFO.resize[VECTOR] = &caller_VECTOR_resize;
    GENERIC_INFO.push[VECTOR] = &caller_VECTOR_push;
    GENERIC_INFO.push_by_value[VECTOR] = &caller_VECTOR_push_by_value;
    GENERIC_INFO.pop[VECTOR] = &caller_VECTOR_pop;
    GENERIC_INFO.insert[VECTOR] = &caller_VECTOR_insert;
    GENERIC_INFO.insert_by_value[VECTOR] = &caller_VECTOR_insert_by_value;
    GENERIC_INFO.rm[VECTOR] = &caller_VECTOR_rm;
    GENERIC_INFO.at[VECTOR] = &caller_VECTOR_at;
    GENERIC_INFO.set[VECTOR] = &caller_VECTOR_set;
    GENERIC_INFO.set_by_value[VECTOR] = &caller_VECTOR_set_by_value;
}

/*-----------------------------------------------------------------------------
 |  Vector Constructor
 ----------------------------------------------------------------------------*/

vector_p new_vector_(const_args_p const named_args)
{
    // If class is not specified, VECTOR will be used
    if (missing_class(named_args->class))
        return GENERIC_INFO.new_vector[VECTOR](named_args);

    // Check the specified class
    check_class(named_args->class);
    return GENERIC_INFO.new_vector[named_args->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Vector Destroyer
 ----------------------------------------------------------------------------*/

void del_vector_(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.del_vector[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Vector Printer
 ----------------------------------------------------------------------------*/

void print_vector_(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.print_vector[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Reserve
 ----------------------------------------------------------------------------*/

void reserve_(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.reserve[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Resize
 ----------------------------------------------------------------------------*/

void resize_(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.resize[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Push
 ----------------------------------------------------------------------------*/

void push_(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.push[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Push By Value
 ----------------------------------------------------------------------------*/

void push_by_value(const_args_p named_args, ...)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);

    va_list ap;
    va_start(ap, named_args);
    GENERIC_INFO.push_by_value[named_args->vector->class](named_args, ap);
    va_end(ap);
}

/*-----------------------------------------------------------------------------
 |  Pop
 ----------------------------------------------------------------------------*/

void pop_(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.pop[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Insert
 ----------------------------------------------------------------------------*/

void insert_(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.insert[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Insert By Value
 ----------------------------------------------------------------------------*/

void insert_by_value(const_args_p named_args, ...)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    va_list ap;
    va_start(ap, named_args);
    GENERIC_INFO.insert_by_value[named_args->vector->class](named_args, ap);
    va_end(ap);
}

/*-----------------------------------------------------------------------------
 |  Remove
 ----------------------------------------------------------------------------*/

void rm_(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.rm[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  At
 ----------------------------------------------------------------------------*/

void *at_(const_args_p const named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    return GENERIC_INFO.at[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Set
 ----------------------------------------------------------------------------*/

void set_(const_args_p named_args)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    GENERIC_INFO.set[named_args->vector->class](named_args);
}

/*-----------------------------------------------------------------------------
 |  Set By Value
 ----------------------------------------------------------------------------*/

void set_by_value(const_args_p named_args, ...)
{
    check_missing_argument(named_args, vector);
    check_class(named_args->vector->class);
    va_list ap;
    va_start(ap, named_args);
    GENERIC_INFO.set_by_value[named_args->vector->class](named_args, ap);
    va_end(ap);
}