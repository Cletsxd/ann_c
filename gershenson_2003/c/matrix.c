#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include "../h/matrix_struct.h"
#include "../h/matrix.h"
#include "../h/error_code.h"

static void (*from_error_code_error_code) (int) = error_code;
static void (*from_error_code_function_number) (int) = function_number;
static void (*from_error_code_good_bye) (void) = good_bye;

struct Matrix;

Matrix create_matrix(int rows, int columns){
    if(rows == 0 || columns == 0){
        from_error_code_error_code(1);
        printf(" Rows: %i - Columns: %i.", rows, columns);
        from_error_code_function_number(1);
        from_error_code_good_bye();
        exit(-1);
    }

    float **matrix;
    matrix = (float**) malloc(rows*sizeof(float*));

    for(int i = 0; i < rows; i++){
        *(matrix + i) = (float*) malloc(columns*sizeof(float));
    }

    Matrix m = {matrix, false, rows, columns};

    return m;
}

Matrix create_null_matrix(){
    Matrix m = {NULL, NULL, NULL, NULL};
    return m;
}

void test_fill_matrix(Matrix *matrix){
    if(is_null_matrix(matrix)){
        from_error_code_error_code(2);
        from_error_code_function_number(2);
        from_error_code_good_bye();
        exit(-1);
    }

    float cont = 0.1;
    float *pa;

    for(int i = 0; i < matrix -> r; i++){
        pa = *(matrix -> vector + i);
        for(int j = 0; j < matrix -> c; j++){
            *(pa + j) = cont;
            cont = cont + 0.1;
        }
    }

    matrix -> fill = true;
}

void fill_matrix(Matrix *matrix){
    if(is_null_matrix(matrix)){
        from_error_code_error_code(2);
        from_error_code_function_number(3);
        from_error_code_good_bye();
        exit(-1);
    }

    float *pa;

    for(int i = 0; i < matrix -> r; i++){
        pa = *(matrix -> vector + i);
        for(int j = 0; j < matrix -> c; j++){
            *(pa + j) = -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)));
        }
    }

    matrix -> fill = true;
}

void show_matrix(Matrix matrix){
    if(is_null_matrix(&matrix)){
        from_error_code_error_code(3);
        from_error_code_function_number(4);
        from_error_code_good_bye();
        exit(-1);
    }

    if(matrix.fill == false){
        from_error_code_error_code(4);
        from_error_code_function_number(4);
        from_error_code_good_bye();
        free_matrix(&matrix);
        exit(-1);
    }

    float *pa;

    printf("[");
    for(int i = 0; i < matrix.r; i++){
        pa = *(matrix.vector + i);
        printf("[");
        for(int j = 0; j < matrix.c; j++){
            printf("%f", *(pa + j));
            if(j != matrix.c - 1){
                printf(", ");
            }
        }
        printf("]");
        if(i != matrix.r - 1){
            printf(",\n");
        }
    }
    printf("]\n");
}

void free_matrix(Matrix *matrix){
    if(is_null_matrix(matrix)){
        from_error_code_error_code(5);
        from_error_code_function_number(5);
        from_error_code_good_bye();
        exit(-1);
    }

    free((void*) matrix -> vector);

    matrix -> vector = NULL;
    matrix -> r = NULL;
    matrix -> c = NULL;
    matrix -> fill = NULL;
}

void fill_set_vector_matrix(Matrix *matrix, int cant_cas, ...){
    if(is_null_matrix(matrix)){
        from_error_code_error_code(2);
        from_error_code_function_number(6);
        from_error_code_good_bye();
        exit(-1);
    }

    va_list pa;

    va_start(pa, cant_cas);

    float *vec = (float*) malloc(cant_cas * sizeof(float));
    float *ap;
    ap = vec;

    int cont_args = 0;

    while(cant_cas--){
        *ap = va_arg(pa, double);
        ap++;
    }

    float *p_vec;
    p_vec = vec;

    for(int i = 0; i < matrix -> r; i++){
        ap = *(matrix -> vector + i);
        for(int j = 0; j < matrix -> c; j++){
            *(ap + j) = *p_vec;
            p_vec++;
        }
    }

    va_end(pa);

    free((void*) vec);

    matrix -> fill = true;
}

bool is_null_matrix(Matrix *matrix){
    bool res = false;
    if(matrix -> vector == NULL || matrix -> c == NULL || matrix -> r == NULL){
        res = true;
    }

    return res;
}

void fill_zeros_matrix(Matrix *matrix){
    if(is_null_matrix(matrix)){
        from_error_code_error_code(2);
        from_error_code_function_number(10);
        from_error_code_good_bye();
        exit(-1);
    }

    float *pa;

    for(int i = 0; i < matrix -> r; i++){
        pa = *(matrix -> vector + i);
        for(int j = 0; j < matrix -> c; j++){
            *(pa + j) = 0.0;
        }
    }

    matrix -> fill = true;
}

/*int main(){
    Matrix prueba = create_matriz(2, 3);

    srand(time(NULL));
    //prueba_llenar_matriz(prueba);
    llenar_matriz(prueba);

    mostrar_matriz(prueba);

    free((void*) prueba.vector);
}*/