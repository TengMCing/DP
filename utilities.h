//
// Created by Patrick Li on 17/7/22.
//

#ifndef VEC_LANG_2_UTILITIES_H
#define VEC_LANG_2_UTILITIES_H

/*-----------------------------------------------------------------------------
 |  Unused arguments
 ----------------------------------------------------------------------------*/

#define UNUSED(x) (void) (x)

/*-----------------------------------------------------------------------------
 |  Deference Or Cast Void Pointer
 ----------------------------------------------------------------------------*/

/// @description Deference void pointer.
#define as_int(void_p) *(int *) void_p

/// @description Deference void pointer.
#define as_long(void_p) *(long *) void_p

/// @description Deference void pointer.
#define as_float(void_p) *(float *) void_p

/// @description Deference void pointer.
#define as_double(void_p) *(double *) void_p

/// @description Deference void pointer.
#define as_char(void_p) *(char *) void_p

/// @description Cast void pointer to char pointer.
#define as_string(void_p) (char *) void_p

#endif//VEC_LANG_2_UTILITIES_H
