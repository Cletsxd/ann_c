#include <stdio.h>
#include <stdlib.h>

#include "matrix_struct.h"
#include "matrix.h"
#include "error_code.h"

static Matrix (*from_matrix_create_matrix) (int, int) = create_matrix;
static void (*from_matrix_show_matrix) (Matrix) = show_matrix;
static void (*from_matrix_fill_set_vector_matrix) (Matrix*, int, ...) = fill_set_vector_matrix;
static void (*from_matrix_free_matrix) (Matrix*) = free_matrix;
static void (*from_matrix_fill_zeros_matrix) (Matrix*) = fill_zeros_matrix;

static void (*from_error_code_error_code) (int) = error_code;
static void (*from_error_code_function_number) (int) = function_number;
static void (*from_error_code_good_bye) (void) = good_bye;

Matrix dot_fuction(Matrix a, Matrix b){
    if(a.c != b.r){
        from_error_code_error_code(8);
        printf(" `a matrix` columns: %i - `b matrix` rows: %i", a.c, b.r);
        from_error_code_function_number(11);
        from_error_code_good_bye();
        exit(-1);
    }

    Matrix res;

    res = from_matrix_create_matrix(a.r, b.c);
    from_matrix_fill_zeros_matrix(&res);

    float *res_aux;
    float *a_aux;
    float *b_aux;

    for(int i = 0; i < a.r; i++){
        res_aux = *(res.vector + i);
        a_aux = *(a.vector + i);

        for(int j = 0; j < b.c; j++){
            float sum = 0.0;

            for(int k = 0; k < a.c; k++){
                b_aux = *(b.vector + k);
                sum = *(a_aux + k) * *(b_aux + j) + sum;
            }

            *(res_aux + j) = sum;
        }
    }

    return res;
}

Matrix sum_wc_fuction(Matrix a, Matrix b){
    if(b.r > 1){
        from_error_code_error_code(9);
        from_error_code_function_number(12);
        from_error_code_good_bye();
        exit(-1);
    }

    if(a.c != b.c){
        from_error_code_error_code(10);
        from_error_code_function_number(12);
        from_error_code_good_bye();
        exit(-1);
    }

    Matrix res;

    res = from_matrix_create_matrix(a.r, a.c);
    from_matrix_fill_zeros_matrix(&res);

    float *res_aux;
    float *a_aux;
    float *b_aux;

    b_aux = *(b.vector + 0);

    for(int i = 0; i < a.r; i++){
        a_aux = *(a.vector + i);
        res_aux = *(res.vector + i);
        for(int j = 0; j < a.c; j++){
            *(res_aux + j) = *(a_aux + j) + *(b_aux + j);
        }
    }

    return res;
}

Matrix subs_matrix_function(Matrix a, Matrix b){
    if(a.r != b.r){
        from_error_code_error_code(11);
        from_error_code_function_number(13);
        from_error_code_good_bye();
        exit(-1);
    }

    if(a.c != b.c){
        from_error_code_error_code(10);
        from_error_code_function_number(13);
        from_error_code_good_bye();
        exit(-1);
    }

    Matrix res = from_matrix_create_matrix(a.r, b.c);
    from_matrix_fill_zeros_matrix(&res);

    float *res_aux;
    float *a_aux;
    float *b_aux;

    for(int i = 0; i < a.r; i++){
        res_aux = *(res.vector + i);
        a_aux = *(a.vector + i);
        b_aux = *(b.vector + i);

        for(int j = 0; j < a.c; j++){
            *(res_aux + j) = *(a_aux + j) - *(b_aux + j);
        }
    }

    return res;
}

int main(){
    /*Matrix a = create_matrix(2, 3);
    from_matrix_fill_set_vector_matrix(
        &a,
        a.c * a.r,
        1.0, 0.0, 1.0,
        0.0, 1.0, 2.0
    );

    Matrix b = create_matrix(3, 2);
    from_matrix_fill_set_vector_matrix(
        &b,
        b.c * b.r,
        3.0, 5.0,
        -1.0, 0.0,
        2.0, -1.0
    );

    Matrix res = dot_fuction(a, b);
    from_matrix_show_matrix(res);

    from_matrix_free_matrix(&a);
    from_matrix_free_matrix(&b);
    from_matrix_free_matrix(&res);*/

    /*Matrix b = create_matrix(1, 3);
    from_matrix_fill_set_vector_matrix(
        &b,
        b.c * b.r,
        1.0, 0.0, 1.0
    );

    Matrix a = create_matrix(3, 3);
    from_matrix_fill_set_vector_matrix(
        &a,
        a.c * a.r,
        3.0, 5.0, 4.0,
        1.0, 6.0, 7.0,
        1.0, 0.0, 1.0
    );

    Matrix res = sum_wc_fuction(a, b);
    from_matrix_show_matrix(res);

    from_matrix_free_matrix(&a);
    from_matrix_free_matrix(&b);
    from_matrix_free_matrix(&res);*/

    /*Matrix a = create_matrix(3, 3);
    from_matrix_fill_set_vector_matrix(
        &a,
        a.c * a.r,
        3.0, 5.0, 4.0,
        1.0, 6.0, 7.0,
        1.0, 0.0, 1.0
    );

    Matrix b = create_matrix(3, 3);
    from_matrix_fill_set_vector_matrix(
        &b,
        b.c * b.r,
        1.0, 7.0, 3.0,
        3.0, 2.0, 8.0,
        4.0, 3.0, 9.0
    );

    Matrix res = subs_matrix_function(a, b);
    from_matrix_show_matrix(res);

    from_matrix_free_matrix(&a);
    from_matrix_free_matrix(&b);
    from_matrix_free_matrix(&res);*/
}