//
// Created by Patrick Li on 16/7/22.
//

#ifndef VEC_LANG_2_ERROR_H
#define VEC_LANG_2_ERROR_H

/*-----------------------------------------------------------------------------
 |  Undefined Type Error
 ----------------------------------------------------------------------------*/

#ifndef UndefinedTypeError

/// @description Macro to raise the undefined type error.
#define UndefinedTypeError(type)                                                                                                                                   \
    {                                                                                                                                                              \
        printf("[UndefinedTypeError]\n\tRaised by function <%s> at line %d of file \"%s\":\n\tUndefined vector type (%d)!\n", __func__, __LINE__, __FILE__, type); \
        exit(EXIT_FAILURE);                                                                                                                                        \
    }
#endif//UndefinedTypeError

/*-----------------------------------------------------------------------------
 |  Undefined Class Error
 ----------------------------------------------------------------------------*/

#ifndef UndefinedClassError

/// @description Macro to raise the undefined class error.
#define UndefinedClassError(class)                                                                                                                                    \
    {                                                                                                                                                                 \
        printf("[UndefinedClassError]\n\tRaised by function <%s> at line %d of file \"%s\":\n\tUndefined vector class (%d)!\n", __func__, __LINE__, __FILE__, class); \
        exit(EXIT_FAILURE);                                                                                                                                           \
    }
#endif//UndefinedClassError

/*-----------------------------------------------------------------------------
 |  Index Out Of Bound Error
 ----------------------------------------------------------------------------*/

#ifndef IndexOutOfBoundError

/// @description Macro to raise the index out of bound error.
#define IndexOutOfBoundError(index)                                                                                                                                \
    {                                                                                                                                                              \
        printf("[IndexOutOfBoundError]\n\tRaised by function <%s> at line %d of file \"%s\":\n\tIndex (%d) out of bound!\n", __func__, __LINE__, __FILE__, index); \
        exit(EXIT_FAILURE);                                                                                                                                        \
    }
#endif//IndexOutOfBoundError

/*-----------------------------------------------------------------------------
 |  Not VEC_VEC_P Error
 ----------------------------------------------------------------------------*/

#ifndef NotVECPError

/// @description Macro to raise the not VEC_VEC_P error.
#define NotVECPError(vec_type)                                                                                                                                          \
    {                                                                                                                                                                   \
        printf("[NotVECPError]\n\tRaised by function <%s> at line %d of file \"%s\":\n\tVector type (%d) is not VEC_VEC_P!\n", __func__, __LINE__, __FILE__, vec_type); \
        exit(EXIT_FAILURE);                                                                                                                                             \
    }
#endif//NotVECPError

/*-----------------------------------------------------------------------------
 |  Unsupported Operand Error
 ----------------------------------------------------------------------------*/

#ifndef UnsupportedOperandError

/// @description Macro to raise the unsupported operand error.
#define UnsupportedOperandError(vec_type_left, vec_type2_right)                                                                                                                                                      \
    {                                                                                                                                                                                                                \
        printf("[UnsupportedOperandError]\n\tRaised by function <%s> at line %d of file \"%s\":\n\tUnsupported operand between type (%d) and (%d)!\n", __func__, __LINE__, __FILE__, vec_type_left, vec_type_right); \
        exit(EXIT_FAILURE);                                                                                                                                                                                          \
    }
#endif//UnsupportedOperandError

/*-----------------------------------------------------------------------------
 |  Zero Item Error
 ----------------------------------------------------------------------------*/

#ifndef ZeroItemError

/// @description Macro to raise the zero item error.
#define ZeroItemError(num_item)                                                                                                                                           \
    {                                                                                                                                                                     \
        printf("[ZeroItemError]\n\tRaised by function <%s> at line %d of file \"%s\":\n\tNumber of items (%d) less than one!\n", __func__, __LINE__, __FILE__, num_item); \
        exit(EXIT_FAILURE);                                                                                                                                               \
    }
#endif//ZeroItemError

/*-----------------------------------------------------------------------------
 |  Missing argument Error
 ----------------------------------------------------------------------------*/

#ifndef MissingArgumentError

/// @description Macro to raise the missing argument error.
#define MissingArgumentError(arg_name)                                                                                                                                         \
    {                                                                                                                                                                          \
        printf("[MissingArgumentError]\n\tRaised by function <%s> at line %d of file \"%s\":\n\tNamed argument \"%s\" is missing!\n", __func__, __LINE__, __FILE__, arg_name); \
        exit(EXIT_FAILURE);                                                                                                                                                    \
    }
#endif//MissingArgumentError

#endif//VEC_LANG_2_ERROR_H
