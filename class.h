//
// Created by Patrick Li on 16/7/22.
//

#ifndef VEC_LANG_2_CLASS_H
#define VEC_LANG_2_CLASS_H

#ifndef VEC_CLASS

/*-----------------------------------------------------------------------------
 |  VEC_CLASS
 ----------------------------------------------------------------------------*/

/// @description Vector classes.
/// @details
/// VECTOR: 0, the default vector class. \n\n
/// NULL_CLASS: 255, null class. This is not an actual vector class. Defined for checking missing arguments.
typedef enum VEC_CLASS
{
    VECTOR = 0,
    NULL_CLASS = 255
} VEC_CLASS;

/// @description Number of vector classes.
#define NUM_CLASS 1
#endif//VEC_CLASS

#endif//VEC_LANG_2_CLASS_H
