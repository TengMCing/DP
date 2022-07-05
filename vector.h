typedef enum VEC_TYPE
{
    VEC_INT = 0,
    VEC_FLOAT = 1,
    VEC_DOUBLE = 2,
    VEC_CHAR = 3,
    VEC_VEC_P = 4
} VEC_TYPE;

typedef struct vector
{
    int size;
    int capacity;
    enum VEC_TYPE type;
    void *data;
} vector_t;

typedef vector_t *vector_p;

void *get(vector_p, int);
void set(vector_p, int, ...);
void delete_vector(vector_p);
vector_p new_vector(VEC_TYPE);
void print_vector_(vector_p, unsigned char);
void resize(vector_p, int);
void push(vector_p, ...);

#define get_ij(v, i, j) get(get(v, i), j)
#define resize_realloc(data, type, size) data = realloc(data, sizeof(type) * size)
#define print_vector(v, depth) \
    print_vector_(v, depth);   \
    printf("\n")

#define as_int(void_p) *((int *)void_p)
#define as_float(void_p) *((float *)void_p)
#define as_double(void_p) *((double *)void_p)
#define as_char(void_p) *((char *)void_p)

#define const_op(op, name)                                               \
    void const_##name(vector_p v, ...)                                   \
    {                                                                    \
        if (v->type == VEC_VEC_P)                                        \
        {                                                                \
            printf("ERROR: unable to add constant to a nested vector!"); \
            exit(1);                                                     \
        }                                                                \
                                                                         \
        va_list ap;                                                      \
        va_start(ap, v);                                                 \
                                                                         \
        if (v->type == VEC_INT)                                          \
        {                                                                \
            int placeholder = va_arg(ap, int);                           \
            for (int i = 0; i < v->size; i++)                            \
            {                                                            \
                set(v, i, as_int(get(v, i)) op placeholder);             \
            }                                                            \
        }                                                                \
                                                                         \
        if (v->type == VEC_FLOAT)                                        \
        {                                                                \
            float placeholder = (float)va_arg(ap, double);               \
            for (int i = 0; i < v->size; i++)                            \
            {                                                            \
                set(v, i, as_float(get(v, i)) op placeholder);           \
            }                                                            \
        }                                                                \
                                                                         \
        if (v->type == VEC_DOUBLE)                                       \
        {                                                                \
            double placeholder = va_arg(ap, double);                     \
            for (int i = 0; i < v->size; i++)                            \
            {                                                            \
                set(v, i, as_double(get(v, i)) op placeholder);          \
            }                                                            \
        }                                                                \
                                                                         \
        if (v->type == VEC_CHAR)                                         \
        {                                                                \
            char placeholder = (char)va_arg(ap, int);                    \
            for (int i = 0; i < v->size; i++)                            \
            {                                                            \
                set(v, i, as_char(get(v, i)) op placeholder);            \
            }                                                            \
        }                                                                \
                                                                         \
        va_end(ap);                                                      \
    }\
