//Raymond Lee
//ID: 116596772
//CSE 220 - HW7

#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    return NULL;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    return NULL;
}

void free_bst_sf(bst_sf *root) {
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    unsigned int rows = mat1->num_rows;
    unsigned int cols = mat1->num_cols;

    size_t n = size_t(rows) * size_t(cols);
    matrix_sf *out = malloc(sizeof(matrix_sf) + n * sizeof(int));
    if (!out)
        return NULL;

    out->name = '?';
    out->num_rows = rows;
    out->num_cols = cols;
    for (size_t i = 0; i < n; ++i)
    {
        out->values[i] = mat1->values[i] + mat2->values[i];
    }

    return out;

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    unsigned int r1 = mat1->num_rows;
    unsigned int c1 = mat1->num_cols; 
    unsigned int c2 = mat2->num_cols;

    size_t n = (size_t)r1 * (size_t)c2;

    matrix_sf *out = malloc(sizeof(matrix_sf) + n * sizeof(int));
    if (!out)
        return NULL;

    out->name = '?';
    out->num_rows = r1;
    out->num_cols = c2;

    for (unsigned int i = 0; i < r1; ++i)
    {
        for (unsigned int j = 0; j < c2; ++j)
        {
            long sum = 0;
            for (unsigned int k = 0; k < c1; ++k)
            {
                size_t idx1 = (size_t)i * c1 + k;
                size_t idx2 = (size_t)k * c2 + j;
                sum += (long)mat1->values[idx1] * (long)mat2->values[idx2];
            }
            out->values[(size_t)i * c2 + j] = (int)sum;

        }
    }

    return out;
    
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    unsigned int in_rows = mat->num_rows;
    unsigned int in_cols = mat->num_cols;

    unsigned int out_rows = in_cols;
    unsigned int out_cols = in_rows;

    size_t n = (size_t)out_rows * (size_t)out_cols;

    matrix_sf *out = malloc(sizeof(matrix_sf) + n * sizeof(int));
    if (!out)
        return NULL;

    out->name = '?';
    out->num_rows = out_rows;
    out->num_cols = out_cols;

    for (unsigned int r = 0; r < in_rows; ++r)
    {
        for (unsigned int c = 0; c < in_cols; ++c)
        {
            size_t in_idx  = (size_t)r * in_cols + c;
            size_t out_idx = (size_t)c * out_cols + r;
            out->values[out_idx] = mat->values[in_idx];
        }
    }
    
    return out;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    const char *p = expr;

    define SKIP_SPACE() 
        while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
            ++p

    SKIP_SPACE();

    char *end = NULL;
    unsigned long ur = strtoul(p, &end, 10);
    p = end;

    SKIP_SPACE();

    unsigned long uc = strtoul(p, &end, 10);
    p = end;

    SKIP_SPACE();

    ++p;

    SKIP_SPACE();

    unsigned int num_rows = (unsigned int)ur;
    unsigned int num_cols = (unsigned int)uc;
    size_t n = (size_t)num_rows * (size_t)num_cols;

    matrix_sf *m = malloc(sizeof(matrix_sf) + n * sizeof(int));
    if (!m)    
        return NULL;

    m->name = name;
    m->num_rows = num_rows;
    m->num_cols = num_cols;

    for (unsigned int r = 0; r < num_rows; ++r)
    {
        for (unsigned int c = 0; c < num_cols; ++c)
        {
            SKIP_SPACE();
            long v = strtol(p, &end, 10);
            p = end;

            m->values[(size_t)r * num_cols + c] = (int)v;
        }
        SKIP_SPACE();
        ++p;
        SKIP_SPACE();
    }
     SKIP_SPACE();
     undef SKIP_SPACE
     return m;
}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
