//
// Created by Patrick Li on 16/7/22.
//

#ifndef VEC_LANG_2_VECTOR_H
#define VEC_LANG_2_VECTOR_H

/*-----------------------------------------------------------------------------
 |  Include size_t, NULL from <stddef.h>
 ----------------------------------------------------------------------------*/

//size_t, NULL
#include <stddef.h>

/*-----------------------------------------------------------------------------
 |  Include VEC_CLASS from "class.h"
 ----------------------------------------------------------------------------*/

#ifndef VEC_LANG_2_CLASS_H
//VEC_CLASS
#include "class.h"
#endif//VEC_LANG_2_CLASS_H

/*-----------------------------------------------------------------------------
 |  6 Basic Vector Types
 ----------------------------------------------------------------------------*/

#ifndef VEC_TYPE

/// @description 6 basic vector types.
/// @details
/// VEC_INT: 0, signed integer type. \n\n
/// VEC_LONG: 1, signed long integer type. \n\n
/// VEC_FLOAT: 2, signed floating type. \n\n
/// VEC_DOUBLE: 3, signed double type. \n\n
/// VEC_CHAR: 4, character type. \n\n
/// VEC_VEC_P: 5, vector pointer type. \n\n
/// VEC_NULL: 255, null type. This is not an actual vector type. Defined for checking missing arguments.
typedef enum VEC_TYPE
{
    VEC_INT = 0,
    VEC_LONG = 1,
    VEC_FLOAT = 2,
    VEC_DOUBLE = 3,
    VEC_CHAR = 4,
    VEC_VEC_P = 5,
    VEC_NULL = 255
} VEC_TYPE;

/// @description Number of vector types.
#define NUM_TYPE 6

/// @description Maximum length of vector name.
#define MAX_TYPE_NAME_LEN 15

// TODO: Add NA to each type.
#endif//VEC_TYPE


/*-----------------------------------------------------------------------------
 |  Vector Struct
 ----------------------------------------------------------------------------*/

#ifndef vector

/// @description Maximum length of vector name.
#define MAX_VEC_NAME_LEN 255

/// @description Default capacity of a vector vector.
#define DEFAULT_VEC_CAPACITY 8

/// @description Vector type.
typedef struct vector vector_t;

/// @description Vector pointer.
typedef vector_t *vector_p;


/// @description Vector struct.
/// @param id: (long). Vector ID for runtime.
/// @param name: (char[MAX_VEC_NAME_LEN]). Name of the vector.
/// @param size: (long). Size of the vector.
/// @param capacity: (long). Capacity of the vector.
/// @param type: (VEC_TYPE). Type of the vector.
/// @param class: (VEC_CLASS). Class of the vector.
/// @param data_p: (void*). Data pointer.
struct vector
{
    unsigned int id;
    char name[MAX_VEC_NAME_LEN];
    unsigned int size;
    unsigned int capacity;
    VEC_TYPE type;
    VEC_CLASS class;
    void *data_p;
};
#endif//vector

/*-----------------------------------------------------------------------------
 |  Vector Info
 ----------------------------------------------------------------------------*/

#ifndef vector_info

/// @description Vector information type.
typedef struct vector_info vector_info_t;

/// @description Vector information struct.
/// @param element_bytes : (size_t[NUM_TYPE]). Storage size of the vector type in bytes.
/// @param type_name : (char[NUM_TYPE][MAX_TYPE_NAME_LEN]). Name of the type.
struct vector_info
{
    size_t element_bytes[NUM_TYPE];
    char type_name[NUM_TYPE][MAX_TYPE_NAME_LEN];
};

/// @description Global variable for storing vector information.
vector_info_t VECTOR_INFO;

/// @description Macro to get the size of the vector type.
#define vec_sizeof(vec_type) VECTOR_INFO.element_bytes[vec_type]

/// @description Initialize vector information.
/// @return No return.
void init_vector_info();
#endif//vector_info


#endif//VEC_LANG_2_VECTOR_H
