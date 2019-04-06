#ifndef _MATRIX_H_
#define _MATRIX_H_

struct Matrix;

Matrix create_matrix(int rows, int columns);
Matrix create_null_matrix();
void test_fill_matrix(Matrix *matrix);
void fill_matrix(Matrix *matrix);
void show_matrix(Matrix matrix);
void free_matrix(Matrix *matrix);
void fill_set_vector_matrix(Matrix *matrix, int cant_cas, ...);
bool is_null_matrix(Matrix *matrix);

#endif