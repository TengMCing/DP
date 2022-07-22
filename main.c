#include "args.h"
#include "generic.h"
#include "vector_method.h"
#include <stdio.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winitializer-overrides"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
int main()
{
    init_vector_info();
    init_generic();
    vector_p v = new_vector(.type = VEC_VEC_P);
    push_by_value(args(.vector = v, .num_item = 4),
                  new_vector(.type = VEC_INT),
                  new_vector(.type = VEC_FLOAT),
                  new_vector(.type = VEC_DOUBLE),
                  new_vector(.type = VEC_VEC_P));
    push_by_value(args(.vector = at(.vector = v, .index = 0), .num_item = 3), 1, 2, 3);
    insert_by_value(args(.vector = at(.vector = v, .index = 0), .index = 1, .num_item = 2), 99, 101);

    push_by_value(args(.vector = at(.vector = v, .index = 1), .num_item = 3), 6.0, 6.0, 6.0);
    push_by_value(args(.vector = at(.vector = v, .index = 2), .num_item = 3), 6.0, 6.0, 6.0);
    push_by_value(args(.vector = at(.vector = v, .index = 3), .num_item = 2),
                  new_vector(.type = VEC_CHAR),
                  new_vector(.type = VEC_CHAR));
    push_by_value(args(.vector = at(.vector = at(.vector = v, .index = 3), .index = 0), .num_item = 2),
                  65, 66);
    print_vector(.vector = v, .depth = 3);
    printf("%u\n", v->capacity);
    printf("%lu\n", sizeof(*args()));
    del_vector(.vector = v, .depth = 10);
    return 0;
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop
