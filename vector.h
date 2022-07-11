//
// Created by Patrick Li on 9/7/22.
//

#ifndef VEC_LANG_VECTOR_H
#define VEC_LANG_VECTOR_H

#endif//VEC_LANG_VECTOR_H

/*-----------------------------------------------------------------------------
 |  Vector Data Structure
 ----------------------------------------------------------------------------*/

/// \n \n Different vector types
/// @description Different vector types.
/// @details
/// VEC_INT : 0 \n
/// VEC_FLOAT: 1 \n
/// VEC_DOUBLE: 2 \n
/// VEC_CHAR: 3 \n
/// VEC_VEC_P: 4
typedef enum VEC_TYPE
{
    VEC_INT = 0,
    VEC_FLOAT = 1,
    VEC_DOUBLE = 2,
    VEC_CHAR = 3,
    VEC_VEC_P = 4
} VEC_TYPE;

typedef enum COPY_TYPE
{
    VEC_ORIGINAL = 0,
    VEC_SHALLOW_COPY = 1
} COPY_TYPE;

#define MAX_VEC_NAME_LEN 255

// \n \n Vector
/// @description Structure of a vector.
/// @param size: (int). Size of the vector.
/// @param capacity: (int). Capacity of the vector.
/// @param type: (VEC_TYPE). Type of the vector.
/// @param data: (void*). Pointer to the actual content.
typedef struct vector
{
    unsigned char copy_type;
    char name[MAX_VEC_NAME_LEN];
    int size;
    int capacity;
    VEC_TYPE type;
    void *data;
} vector_t;

/// \n \n Pointer to vector
/// @description Pointer to vector.
typedef vector_t *vector_p;

/*-----------------------------------------------------------------------------
 |  General Vector APIs
 ----------------------------------------------------------------------------*/

/// \n \n Vector constructor
/// @description This function allocates memory for a vector for a given type. \n
/// Destroy this vector with `delete_vector()`.
/// @param vec_type: (VEC_TYPE). Vector type.
/// @return (vector_p). A pointer to a vector.
vector_p new_vector(VEC_TYPE vec_type);

/// \n \n Vector destroyer
/// @description This function deallocates memory for a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @return No return value, called for side effects.
void delete_vector(vector_p vector);

/// \n \n Get an item from a vector
/// @description This function gets the memory address of an (int/float/double/char) or
/// the pointer to the inner vector. Boundaries will be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (void*) A void pointer pointing to that memory address.
void *get(vector_p vector, int index);

/// \n \n Assign value to an item of a vector
/// @description This function assigns a value to an item of a vector. Boundaries will be checked.
/// @details It will cast the input as what `vector->type` indicated.
/// So make sure value of the correct type is passed.
/// @warning Replacing an existing vector with another vector could lead to memory leak if
/// there are any other pointers pointing to the existing vector. \n
/// As a variadic function, it will promote (float) to (double) and (char) to (int) as input.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @param ...: (int/float/double/char/vector_p). Item to be assigned.
/// @return (vector_p) A pointer to the input vector.
vector_p set(vector_p vector, int index, ...);

/// \n \n Print a vector
/// @description This function prints a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param depth: (unsigned char). Depth to print.
/// @return No return value, called for side effects.
void print_vector_(vector_p vector, unsigned char depth);

/// \n \n Print a vector and a '\\n'
/// @description This macro prints a vector and a '\\n'.
/// @param vector: (vector_p). A pointer to a vector.
/// @param depth: (unsigned char). Depth to print.
/// @return No return value, called for side effects.
#define print_vector(vector, depth) \
    print_vector_(vector, depth);   \
    printf("\n")

/// \n \n Resize a vector
/// @description This function increases the capacity of a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param size: (int). Target size.
/// @return (vector_p) A pointer to the input vector.
vector_p resize(vector_p vector, int size);

/// \n \n Create a shallow copy
/// @description This function creates a shallow copy. Only the first layer will be copied. \n
/// Destroy this copy with `delete_vector()` or `delete_copy()`.
/// @param vector: (vector_p). A pointer to a vector.
/// @return (vector_p) A pointer to a shallow copy of the vector.
vector_p copy(vector_p vector);

/// \n \n Copy destroyer
/// @description This function deallocates memory of the shallow copy.
/// @param vector: (vector_p). A pointer to a vector.
/// @return No return value, called for side effects.
void delete_copy(vector_p vector);

/// \n \n Create a deepcopy
/// @description This function creates a deepcopy. \n
/// Destroy this copy with `delete_vector()`.
/// @param vector: (vector_p). A pointer to a vector.
/// @return (vector_p) A pointer to a deepcopy of the vector.
vector_p deepcopy(vector_p vector);

/// \n \n Push an item to a vector
/// @description This function pushes an item to a vector.
/// @details It will cast the input as what `vector->type` indicated.
/// So make sure value of the correct type is passed. \n
/// As a variadic function, it will promote (float) to (double) and (char) to (int) as input.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char/vector_p). An item to be pushed.
/// @return (vector_p) A pointer to the input vector.
vector_p push(vector_p vector, ...);

/// \n \n Push arbitrary items to a vector
/// @description This function pushes arbitrary items to a vector.
/// @details It will cast inputs as what `vector->type` indicated.
/// So make sure value of the correct type is passed. \n
/// As a variadic function, it will promote (float) to (double) and (char) to (int) as input.
/// @param vector: (vector_p). A pointer to a vector.
/// @param num_item: (int). Number of items.
/// @param ...: (int/float/double/char/vector_p). Items to be pushed.
/// @return (vector_p) A pointer to the input vector.
vector_p push_many(vector_p vector, int num_item, ...);

/// \n \n Pop an item to a vector
/// @description This function pops an item from a vector.
/// @details Existing inner vector will be deleted before popping.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (vector_p) A pointer to the input vector.
vector_p pop(vector_p vector, int index);

/// \n \n Call get() twice
/// @description This macro calls get() twice.
/// @param vector: (vector_p). A pointer to a vector.
/// @param i: (int). First Index.
/// @param j: (int). Second Index.
/// @return (void*) A void pointer pointing to that memory address.
#define get_ij(vector, i, j) get(get(v, i), j)

/*-----------------------------------------------------------------------------
 |  Detailed Vector APIs
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 |  Get
 ----------------------------------------------------------------------------*/

/// \n \n Get an item from a vector for a given type
/// @description This macro gets an (int/float/double/char/vector_p) from a vector.
/// Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return One of (int/float/double/char/vector_p).
#define get_type(vector, index, vec_type) \
    ((vec_type *) (vector)->data)[index]

/// \n \n Get an integer value from a vector
/// @description This macro gets an integer from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (int) An integer value.
#define get_int(vector, index) get_type(vector, index, int)

/// \n \n Get a float value from a vector
/// @description This macro gets a float from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (float) A float value.
#define get_float(vector, index) get_type(vector, index, float)

/// \n \n Get a double value from a vector
/// @description This macro gets a double from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (double) A double value.
#define get_double(vector, index) get_type(vector, index, double)

/// \n \n Get a character value from a vector
/// @description This macro gets a character from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (char) A character value.
#define get_char(vector, index) get_type(vector, index, char)

/// \n \n Get a pointer to vector from a vector
/// @description This macro gets a pointer to vector from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (vector_p) A pointer to vector.
#define get_vector_p(vector, index) get_type(vector, index, vector_p)

/*-----------------------------------------------------------------------------
 |  Push
 ----------------------------------------------------------------------------*/

/// \n \n Push an item for a given type to a vector
/// @description This macro pushes an item for a given type to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param item: (int/float/double/char/vector_p). An item to be pushed.
/// @param vec_type: One of (int), (float), (double), (char) and (vector_p). Type of the item.
/// @return No return value, called for side effects.
#define push_type(vector, item, vec_type)                 \
    resize(vector, vector->size + 1);                     \
    ((vec_type *) (vector)->data)[(vector)->size] = item; \
    vector->size += 1

/// \n \n Push an integer value to a vector
/// @description This macro pushes an integer value to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param item: (int). An integer value.
/// @return No return value, called for side effects.
#define push_int(vector, item) \
    push_type(vector, item, int)

/// \n \n Push a float value to a vector
/// @description This macro pushes a float value item to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param item: (float). A float value.
/// @return No return value, called for side effects.
#define push_float(vector, item) \
    push_type(vector, item, float)

/// \n \n Push a double value to a vector
/// @description This macro pushes a double value to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param item: (double). A double value.
/// @return No return value, called for side effects.
#define push_double(vector, item) \
    push_type(vector, item, double)

/// \n \n Push a character value to a vector
/// @description This macro pushes a character value to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param item: (char). A character value.
/// @return No return value, called for side effects.
#define push_char(vector, item) \
    push_type(vector, item, char)

/// \n \n Push a pointer to vector to a vector
/// @description This macro pushes a pointer to vector to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param item: (vector_p). A pointer to vector.
/// @return No return value, called for side effects.
#define push_vector_p(vector, item) \
    push_type(vector, item, vector_p)

/*-----------------------------------------------------------------------------
 |  Pop
 ----------------------------------------------------------------------------*/

/// \n \n Pop an item for a given type from a vector
/// @description This macro pops an item for a given type from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @param vec_type: One of (int), (float), (double), (char) and (vector_p). Type of the item.
/// @return No return value, called for side effects.
#define pop_type(vector, index, vec_type)                          \
    if ((index) < (vector)->size - 1)                              \
        memmove((vec_type *) (vector)->data + (index),             \
                (vec_type *) (vector)->data + (index) + 1,         \
                ((vector)->size - (index) -1) * sizeof(vec_type)); \
    set_##vec_type(vector, (vector)->size - 1, 0);                 \
    (vector)->size -= 1

/// \n \n Pop an integer value from a vector
/// @description This macro pops an integer from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @return No return value, called for side effects.
#define pop_int(vector, index) pop_type(vector, index, int)

/// \n \n Pop a float value from a vector
/// @description This macro pops a float value from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @return No return value, called for side effects.
#define pop_float(vector, index) pop_type(vector, index, float)

/// \n \n Pop a double value from a vector
/// @description This macro pops a double value from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @return No return value, called for side effects.
#define pop_double(vector, index) pop_type(vector, index, double)

/// \n \n Pop a character value from a vector
/// @description This macro pops a character value from a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @return No return value, called for side effects.
#define pop_char(vector, index) pop_type(vector, index, char)

/// \n \n Pop a pointer to vector from a vector
/// @description This macro pops a pointer to vector from a vector. Boundaries will not be checked.
/// @warning The existing vector will not be deleted! This could lead to memory leak!
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @return No return value, called for side effects.
#define pop_vector_p(vector, index) pop_type(vector, index, vector_p)

/*-----------------------------------------------------------------------------
 |  Set
 ----------------------------------------------------------------------------*/

/// \n \n Assign an item for a given type to a vector
/// @description This macro assigns an item for a given type to a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @param item: (int/float/double/char/vector_p). An item to be pushed.
/// @param vec_type: One of (int), (float), (double), (char) and (vector_p). Type of the item.
/// @return No return value, called for side effects.
#define set_type(vector, index, item, vec_type) \
    ((vec_type *) (vector)->data)[index] = item

/// \n \n Assign an integer value to a vector
/// @description This macro assigns an integer value to a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @param item: (integer). An integer value.
/// @return No return value, called for side effects.
#define set_int(vector, index, item) \
    set_type(vector, index, item, int)


/// \n \n Assign a float value to a vector
/// @description This macro assigns a float value to a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @param item: (float). A float value.
/// @return No return value, called for side effects.
#define set_float(vector, index, item) \
    set_type(vector, index, item, float)

/// \n \n Assign a double value to a vector
/// @description This macro assigns a double value to a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @param item: (double). A double value.
/// @return No return value, called for side effects.
#define set_double(vector, index, item) \
    set_type(vector, index, item, double)

/// \n \n Assign a character value to a vector
/// @description This macro assigns a character value to a vector. Boundaries will not be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @param item: (char). A character value.
/// @return No return value, called for side effects.
#define set_char(vector, index, item) \
    set_type(vector, index, item, char)

/// \n \n Assign a pointer to vector to a vector
/// @description This macro assigns a pointer to vector to a vector. Boundaries will not be checked. \n \n
/// @warning The existing vector will not be deleted! This could lead to memory leak!
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: Index of the item.
/// @param item: (vector_p). A pointer to vector.
/// @return No return value, called for side effects.
#define set_vector_p(vector, index, item) \
    set_type(vector, index, item, vector_p)


/*-----------------------------------------------------------------------------
 |  Memory Reallocation Shortcut
 ----------------------------------------------------------------------------*/

/// \n \n Reallocate the memory pointed by a pointer
/// @description This macro reallocates the memory pointed by a pointer.
/// @param pointer: (void*). A pointer.
/// @param type: (atomic type). Type of the data the pointer pointing to.
/// @param size: (int). Target size.
/// @return No return value, called for side effects.
#define resize_realloc(pointer, type, size) pointer = realloc(pointer, sizeof(type) * (size))

/*-----------------------------------------------------------------------------
 |  Cast Void Pointer to Atomic Types
 ----------------------------------------------------------------------------*/

/// \n \n Cast void pointer to integer pointer and dereference it
/// @description This macro casts a void pointer to an integer pointer and dereferences it.
/// @param void_p: (void*). A void pointer.
/// @return (int) An integer value.
#define as_int(void_p) *((int *) (void_p))

/// \n \n Cast void pointer to float pointer and dereference it
/// @description This macro casts a void pointer to a float pointer and dereferences it.
/// @param void_p: (void*). A void pointer.
/// @return (float) A float value.
#define as_float(void_p) *((float *) (void_p))

/// \n \n Cast void pointer to double pointer and dereference it
/// @description This macro casts a void pointer to a double pointer and dereferences it.
/// @param void_p: (void*). A void pointer.
/// @return (double) A double value.
#define as_double(void_p) *((double *) (void_p))

/// \n \n Cast void pointer to char pointer and dereference it
/// @description This macro casts a void pointer to a character pointer and dereferences it.
/// @param void_p: (void*). A void pointer.
/// @return (char) A character value.
#define as_char(void_p) *((char *) (void_p))

/*-----------------------------------------------------------------------------
 |  Binary Operators
 ----------------------------------------------------------------------------*/

#define const_op(op, name)                                                   \
    vector_p const_##name(vector_p vector, ...)                              \
    {                                                                        \
        if (vector->type == VEC_VEC_P)                                       \
            UnsupportedOperandError;                                         \
                                                                             \
        va_list ap;                                                          \
        va_start(ap, vector);                                                \
                                                                             \
        switch (vector->type)                                                \
        {                                                                    \
        case VEC_INT:                                                        \
        {                                                                    \
            int placeholder = va_arg(ap, int);                               \
            for (int i = 0; i < vector->size; i++)                           \
                set_int(vector, i, get_int(vector, i) op placeholder);       \
            break;                                                           \
        }                                                                    \
        case VEC_FLOAT:                                                      \
        {                                                                    \
            float placeholder = (float) va_arg(ap, double);                  \
            for (int i = 0; i < vector->size; i++)                           \
                set_float(vector, i, get_float(vector, i) op placeholder);   \
            break;                                                           \
        }                                                                    \
        case VEC_DOUBLE:                                                     \
        {                                                                    \
            double placeholder = va_arg(ap, double);                         \
            for (int i = 0; i < vector->size; i++)                           \
                set_double(vector, i, get_double(vector, i) op placeholder); \
            break;                                                           \
        }                                                                    \
        case VEC_CHAR:                                                       \
        {                                                                    \
            char placeholder = (char) va_arg(ap, int);                       \
            for (int i = 0; i < vector->size; i++)                           \
                set_char(vector, i, get_char(vector, i) op placeholder);     \
            break;                                                           \
        }                                                                    \
        default:                                                             \
            UndefinedTypeError;                                              \
        }                                                                    \
                                                                             \
        va_end(ap);                                                          \
        return vector;                                                       \
    }

/// \n \n Add a constant to a vector
/// @description This function adds a constant to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_add(vector_p vector, ...);

/// \n \n Subtract a constant from a vector
/// @description This function subtracts a constant from a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_sub(vector_p vector, ...);

/// \n \n Multiply a constant to a vector
/// @description This function multiplies a constant to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_mul(vector_p vector, ...);

/// \n \n Divide a vector by a constant
/// @description This function divides a vector by a constant.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_div(vector_p vector, ...);

/*-----------------------------------------------------------------------------
 |  Errors
 ----------------------------------------------------------------------------*/

/// \n \n Undefined type error
/// @description This macro raises the undefined type error.
/// @return No return value, called for side effects.
#define UndefinedTypeError                       \
    {                                            \
        printf("ERROR: Undefined vector type!"); \
        exit(1);                                 \
    }

/// \n \n Index out of bound error
/// @description This macro raises the index out of bound error.
/// @return No return value, called for side effects.
#define IndexOutOfBoundError                  \
    {                                         \
        printf("ERROR: Index out of bound!"); \
        exit(1);                              \
    }

/// \n \n Unsupported operand error
/// @description This macro raises the unsupported operand error.
/// @return No return value, called for side effects.
#define UnsupportedOperandError                \
    {                                          \
        printf("ERROR: Unsupported operand!"); \
        exit(1);                               \
    }