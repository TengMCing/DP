#include <stdlib.h>
#include <stdio.h>

/* Define a struct for matrix */
struct matrix_
{
    /* Number of rows */
    int n;
    /* Number of columns */
    int p;
    /* A pointer to pointer to float which contains the elements */
    float **data;
};

/* Define a name alias */
typedef struct matrix_ matrix;

/* Syntax sugar for setting value for matrix */
#define set(x, i, j, value) x->data[j][i] = value

/* Syntax sugar for extracting value from matrix */
#define at(x, i, j) x->data[j][i]

/* Syntax sugar for looping through the matrix */
#define for_ij(i_bound, j_bound, inner_job) \
    for (int i = 0; i < i_bound; i++)       \
    {                                       \
        for (int j = 0; j < j_bound; j++)   \
        {                                   \
            inner_job;                      \
        }                                   \
    }

#define for_ij_before(i_bound, j_bound, inner_job, outer_job_before) \
    for (int i = 0; i < i_bound; i++)                                \
    {                                                                \
        outer_job_before;                                            \
        for (int j = 0; j < j_bound; j++)                            \
        {                                                            \
            inner_job;                                               \
        }                                                            \
    }

#define for_ij_after(i_bound, j_bound, inner_job, outer_job_after) \
    for (int i = 0; i < i_bound; i++)                              \
    {                                                              \
        for (int j = 0; j < j_bound; j++)                          \
        {                                                          \
            inner_job;                                             \
        }                                                          \
        outer_job_after;                                           \
    }

/* Memory management - Allocation */
matrix *allocate_mat(const int n, const int p)
{
    /* New a matrix */
    /* Allocate memory for the struct - two ints, one pointer to pointer to float (~16 bytes) */
    matrix *x = malloc(sizeof(matrix));

    /* Store dimensions information */
    x->n = n;
    x->p = p;

    /* Allocate memory for pointer to p columns */
    x->data = malloc(p * sizeof(float *));

    /* Allocate memory for each column - pointer to n floats */
    for (int j = 0; j < p; j++)
    {
        x->data[j] = calloc(n, sizeof(float));
    }

    /* Return the pointer to struct */
    return x;
}

/* Memory management - Free */
void free_mat(matrix *const x)
{
    /* Free p columns first - pointer to n floats */
    for (int j = 0; j < x->p; j++)
    {
        free(x->data[j]);
    }

    /* Free the pointer to p columns */
    free(x->data);

    /* Free the pointer to struct */
    free(x);
}

/* Format and print the matrix */
void print_mat(matrix *const x)
{
    /* Print the dimension information */
    printf("[%d, %d]\n\n", x->n, x->p);

    /* Print elements */
    for_ij_after(x->n, x->p, printf("%5.1f", at(x, i, j)), printf("\n"));

    printf("\n");
}

/* Set the matrix to be a zero matrix  */
void zero_mat(matrix *const x)
{
    for_ij(x->n, x->p, set(x, i, j, 0.0));
}

/* Set the matrix to be an diagonal matrix */
void diag_mat(matrix *const x, const float value)
{
    if (x->n != x->p)
    {
        printf("Warning: unable to build diagonal matrix due to n != p!");
        return;
    }

    for_ij(x->n, x->p,
           if (i != j)
               set(x, i, j, 0.0);
           else set(x, i, i, value););
}

/* Set the matrix to be an identity matrix */
void identity_mat(matrix *x)
{
    diag_mat(x, 1.0);
}

/* Dot product between ith row in X and jth column in Y */
float dot_mat(matrix *const x, matrix *const y, const int i, const int j)
{
    float sum = 0.0;

    /* Peform a dot product */
    for (int k = 0; k < x->p; k++)
    {
        sum += at(x, i, k) * at(y, k, j);
    }

    return sum;
}

/* Matrix multiplication between two matrices */
matrix *mul_mat(matrix *const x, matrix *const y)
{
    /* Check compatiblity */
    if (x->p != y->n)
    {
        printf("Warning: unable to calculate matrix multiplication due to two matrices are not compatible!");
        return NULL;
    }

    /* New a matrix for storing result */
    matrix *result_mat = allocate_mat(x->n, y->p);

    /* Compute the dot product and set values for each element of the result matrix */
    for_ij(x->n, x->p, set(result_mat, i, j, dot_mat(x, y, i, j)));

    /* Return the result matrix */
    return result_mat;
}

/* Scalar multiply matrix */
matrix *scalar_mul_mat(matrix *const x, const float a)
{
    /* New a matrix for storing result */
    matrix *result_mat = allocate_mat(x->n, x->p);

    /* Times element by scalar */
    for_ij(x->n, x->p, set(result_mat, i, j, at(x, i, j) * a));

    /* Return the result matrix */
    return result_mat;
}

/* Scalar multiply matrix in place */
void scalar_mul_equal_mat(matrix *const x, const float a)
{
    /* Times element by scalar */
    for_ij(x->n, x->p, set(x, i, j, at(x, i, j) * a));
}

/* Scalar plus matrix */
matrix *scalar_plus_mat(matrix *const x, const float a)
{
    /* New a matrix for storing result */
    matrix *result_mat = allocate_mat(x->n, x->p);

    /* Plus element by scalar */
    for_ij(x->n, x->p, set(result_mat, i, j, at(x, i, j) + a));

    /* Return the result matrix */
    return result_mat;
}

/* Scalar plus matrix in place */
void scalar_plus_equal_mat(matrix *const x, const float a)
{
    /* Plus element by scalar */
    for_ij(x->n, x->p, set(x, i, j, at(x, i, j) + a));
}

/* Transpose a matrix */
matrix *t_mat(matrix *const x)
{
    /* New a matrix for storing the matrix transpose */
    matrix *result_mat = allocate_mat(x->p, x->n);

    /* Set elements for the result matrix */
    for_ij(x->n, x->p, set(result_mat, j, i, at(x, i, j)));

    /* Return the result matrix */
    return result_mat;
}

int main(int argc, char const *argv[])
{
    matrix *x = allocate_mat(1, 1);
    matrix *y = allocate_mat(1, 2);

    diag_mat(x, 3.0);
    print_mat(x);

    x->data[0][0] = 2;
    y->data[0][0] = 3;
    y->data[1][0] = 4;

    print_mat(x);
    print_mat(y);

    matrix *z = mul_mat(x, y);
    print_mat(z);
    free_mat(z);

    z = t_mat(y);
    print_mat(z);

    scalar_mul_equal_mat(z, 2);
    print_mat(z);

    scalar_plus_equal_mat(z, -10);
    print_mat(z);

    free_mat(x);
    free_mat(y);
    free_mat(z);

    // printf("%lu", sizeof(matrix));

    return 0;
}
