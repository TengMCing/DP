#include "eval.h"
#include "vector.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    vector_p v = new_vector(VEC_VEC_P);

    push(v, new_vector(VEC_INT));
    push(get(v, 0), 2);
    push_many(get(v, 0), 2, 1, 'a');
    print_vector(const_mul(const_add(get(v, 0), 10), 2), 1);

    pop(get_vector_p(v, 0), 2);

    push(v, new_vector(VEC_CHAR));
    print_vector(push_many(get(v, 1), 3, 'A', 'B', 'C'), 1);


    const_add(get(v, 1), 10);
    const_div(get(v, 1), 2);

    push(v, new_vector(VEC_FLOAT));
    push(get(v, 2), 1.0f);
    push(get(v, 2), 2.0f);

    const_add(get(v, 2), 10.0);
    const_sub(get(v, 2), 2.0);

    push(v, new_vector(VEC_DOUBLE));
    push(get(v, 3), 1.0);
    push(get(v, 3), 3.0);

    const_add(get(v, 3), 10.0);
    const_mul(get(v, 3), 2.0);

    push(v, new_vector(VEC_VEC_P));
    push(get(v, 4), new_vector(VEC_INT));
    push(get(get(v, 4), 0), 1);
    push_many(get_ij(v, 4, 0), 3, 3, 2, 1);

    resize(v, 100);

    print_vector(v, 3);
    pop(v, 1);
    print_vector(v, 3);

    // print_vector(*(vector_p *) (((char *) v->data) + 8), 3);

    vector_p v2 = deepcopy(v);
    print_vector(*(vector_p *) (((char *) v2->data) + 8), 3);
    print_vector(v2, 3);

    delete_vector(v);
    delete_vector(v2);

    char tt[] = "NEW v VEC_INT";
    eval(tt);
    // printf("%s", tt);

    return 0;
}