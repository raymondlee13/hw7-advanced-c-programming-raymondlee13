//Raymond Lee
//ID: 116596772
//CSE 220 - HW7

#include "hw7.h"
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    if (!mat) 
        return root;

    if (!root)
    {
        bst_sf *node = (bst_sf *)malloc(sizeof(bst_sf));
        if (!node) 
            return NULL;
        node->mat = mat;
        node->left_child = NULL;
        node->right_child = NULL;
        return node;
    }

    bst_sf *parent = NULL;
    bst_sf *curr = root;
    while (curr)
    {
        parent = curr;
        if (mat->name < curr->mat->name)
        {
            curr = curr->left_child;
        }
        else
        {
            curr = curr->right_child;
        }
    }

    bst_sf *node = (bst_sf *)malloc(sizeof(bst_sf));
    if (!node)
        return root;
    node->mat = mat;
    node->left_child = NULL;
    node->right_child = NULL;

    if (mat->name < parent->mat->name)
    {
        parent->left_child = node;
    }
    else
    {
        parent->right_child = node;
    }

    return root;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    bst_sf *curr = root;
    while (curr)
    {
        if (name == curr->mat->name)
        {
            return curr->mat;
        }
        else if (name < curr->mat->name)
        {
            curr = curr->left_child;
        }
        else
        {
            curr = curr->right_child;
        }
    }
    return NULL; 
}

void free_bst_sf(bst_sf *root) {
    if (!root)
        return;
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    if (root->mat)
    {
        free(root->mat);
        root->mat = NULL;
    }

    free(root);
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    unsigned int rows = mat1->num_rows;
    unsigned int cols = mat1->num_cols;

    size_t n = (size_t)rows * (size_t)cols;
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
}

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

    while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
        ++p;

    char *end = NULL;
    unsigned long ur = strtoul(p, &end, 10);
    p = end;

    while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
        ++p;

    unsigned long uc = strtoul(p, &end, 10);
    p = end;

    while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
        ++p;

    ++p;

    while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
        ++p;

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
            while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
                ++p;
            long v = strtol(p, &end, 10);
            p = end;

            m->values[(size_t)r * num_cols + c] = (int)v;
        }
        while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
            ++p;
        ++p;
        while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
            ++p;
    }
    while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
        ++p;
    return m;
}

char* infix2postfix_sf(char *infix) {
    if (!infix)
        return NULL;

    size_t n = strlen(infix);
    char *out = (char *)malloc(n + 1);
    if (!out)
        return NULL;

    char *ops = (char *)malloc(n + 1);
    if (!ops)
    {
        free(out);
        return NULL; 
    }
    int top = -1;

    size_t k = 0;

    for (size_t i = 0; i < n; ++i)
    {
        char ch = infix[i];
        if (ch==' ' || ch=='\t' || ch=='\n' || ch=='\r' || ch=='\f' || ch=='\v')
            continue;

        if (ch >= 'A' && ch <= 'Z')
        {
            out[k++] = ch;
        }
        else if (ch == '\'')
        {
            out[k++] = '\'';
        }
        else if (ch == '(')
        {
            ops[++top] = ch;
        }
        else if (ch == ')')
        {
            while (top >= 0 && ops[top] != '(')
            {
                out[k++] = ops[top--];
            }
            if (top >= 0 && ops[top] == '(')
            {
                --top;
            }
        }
        else if (ch == '+' || ch == '*')
        {
            int new_prec;
            if (ch == '+')
            {
                new_prec = 1;
            }
            else
            {
            new_prec = 2;
            }

            while (top >= 0 && ops[top] != '(')
            {
            int top_prec = -1;
            if (ops[top] == '+')
                top_prec = 1;
            else if (ops[top] == '*')
                top_prec = 2;

            if (top_prec >= new_prec)
                out[k++] = ops[top--];
            else
                break;
            }
        ops[++top] = ch;
        }
    }
    while (top >= 0)
    {
        if (ops[top] != '(') out[k++] = ops[top];
        --top;
    }
    out[k] = '\0';
    free(ops);
    return out;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    if (!expr)
        return NULL;

    char *postfix = infix2postfix_sf(expr);
    if (!postfix)
        return NULL;

    size_t n = strlen(postfix);
    matrix_sf **stack = (matrix_sf **)malloc((n + 1) * sizeof(matrix_sf *));
    if (!stack)
    {
        free(postfix); 
        return NULL;
    }
    int top = -1;

    for (size_t i = 0; i < n; ++i)
    {
        char ch = postfix[i];

        if (ch==' ' || ch=='\t' || ch=='\n' || ch=='\r' || ch=='\f' || ch=='\v')
            continue;

        if (ch >= 'A' && ch <= 'Z')
        {
            matrix_sf *m = find_bst_sf(ch, root);
            if (!m)
            {
                free(postfix);
                free(stack);
                return NULL;
            }
            stack[++top] = m;
        }
        else if (ch == '\'')
        {
            if (top < 0)
            {
                free(postfix);
                free(stack);
                return NULL;
            }
            matrix_sf *a = stack[top--];
            matrix_sf *t = transpose_mat_sf(a);
            if (!t)
            {
                free(postfix);
                free(stack);
                return NULL;
            }

            if (!(a->name >= 'A' && a->name <= 'Z'))
            {
                free(a);
            }
            stack[++top] = t;
        }
        else if (ch == '+' || ch == '*')
        {
            if (top < 1)
            {
                if (top == 0 && stack[0] && !(stack[0]->name >= 'A' && stack[0]->name <= 'Z'))
                    free(stack[0]);
                free(postfix);
                free(stack);
                return NULL;
            }
            matrix_sf *b = stack[top--];
            matrix_sf *a = stack[top--];

            matrix_sf *res = NULL;
            if (ch == '+')
            {
                res = add_mats_sf(a, b);
            }
            else
            {
                res = mult_mats_sf(a, b);
            }

            if (a && !(a->name >= 'A' && a->name <= 'Z'))
            {
                free(a);
            }
            if (b && !(b->name >= 'A' && b->name <= 'Z'))
            {
                free(b);
            }

            if (!res)
            {
                free(postfix);
                free(stack);
                return NULL;
            }
            
            top += 1;
            stack[top] = res;
        }
        else
        {
            continue;
        }
    }
    matrix_sf *result = NULL;
    if (top >= 0)
    {
        result = stack[top];
        top -= 1;
    }

    while (top >= 0)
    {
        matrix_sf *m = stack[top];
        if (m && !(m->name >= 'A' && m->name <= 'Z'))
        {
            free(m);
        }
        top -= 1;
    }

    free(postfix);
    free(stack);

    if (!result)
        return NULL;

    result->name = name;
    return result;
}

matrix_sf *execute_script_sf(char *filename) {
    if (!filename)
        return NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp)
        return NULL;

    bst_sf *root = NULL;
    matrix_sf *last = NULL;

    char *line = NULL;
    size_t cap = 0;
    while (1)
    {
        ssize_t got = getline(&line, &cap, fp);
        if (got < 0)
            break;

        const char *p = line;
        while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v')
            ++p;

        if (*p == '\0')
            continue;

        char name = *p;
        while (*p && *p != '=')
            ++p;

        if (!*p)
            continue;
        ++p;

        while (*p==' ' || *p=='\t' || *p=='\n' || *p=='\r' || *p=='\f' || *p=='\v') 
            ++p;

        char *rhs = (char *)p;

        int is_definition = 0;
        const char *q = rhs;
        while (*q)
        {
            if (*q == '[')
            {
                is_definition = 1;
                break;
            }
            ++q;
        }
        matrix_sf *m = NULL;
        if (is_definition)
        {
            m = create_matrix_sf(name, rhs);
        }
        else
        {
            m = evaluate_expr_sf(name, rhs, root);
        }

        if (!m)
        {
            if (line) free(line);
            fclose(fp);
            return NULL;
        }

        root = insert_bst_sf(m, root);

        last = m;
    }

    if (line)
        free(line);
    fclose(fp);

    return last;
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
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++)
    {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}


