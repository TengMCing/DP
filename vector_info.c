//
// Created by Patrick Li on 17/7/22.
//

#include "vector.h"
#include <string.h>

/*-----------------------------------------------------------------------------
 |  Initialize Vector Info
 ----------------------------------------------------------------------------*/

void init_vector_info()
{
    VECTOR_INFO.element_bytes[VEC_INT] = sizeof(int);
    VECTOR_INFO.element_bytes[VEC_LONG] = sizeof(long);
    VECTOR_INFO.element_bytes[VEC_FLOAT] = sizeof(float);
    VECTOR_INFO.element_bytes[VEC_DOUBLE] = sizeof(double);
    VECTOR_INFO.element_bytes[VEC_CHAR] = sizeof(char);
    VECTOR_INFO.element_bytes[VEC_VEC_P] = sizeof(vector_p);

    memcpy(VECTOR_INFO.type_name[VEC_INT], "VEC_INT", strlen("VEC_INT"));
    memcpy(VECTOR_INFO.type_name[VEC_LONG], "VEC_LONG", strlen("VEC_LONG"));
    memcpy(VECTOR_INFO.type_name[VEC_FLOAT], "VEC_FLOAT", strlen("VEC_FLOAT"));
    memcpy(VECTOR_INFO.type_name[VEC_DOUBLE], "VEC_DOUBLE", strlen("VEC_DOUBLE"));
    memcpy(VECTOR_INFO.type_name[VEC_CHAR], "VEC_CHAR", strlen("VEC_CHAR"));
    memcpy(VECTOR_INFO.type_name[VEC_VEC_P], "VEC_VEC_P", strlen("VEC_VEC_P"));
}