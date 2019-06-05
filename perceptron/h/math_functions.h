#ifndef _MATH_FUNCTIONS_H_
#define _MATH_FUNCTIONS_H_

struct Matrix;

Matrix dot_function(Matrix a, Matrix b);
Matrix sum_wc_function(Matrix a, Matrix b);
Matrix subs_matrix_function(Matrix a, Matrix b);
Matrix deriv_e2medio_function(Matrix a, Matrix b);
Matrix mult_matrix_function(Matrix a, Matrix b);
Matrix mean_matrix_function(Matrix mat);
Matrix mult_matrix_float_function(Matrix mat, float num);
Matrix sigmoidal_act_function(Matrix mat);
Matrix tanh_act_function(Matrix mat);
Matrix relu_act_function(Matrix mat);
Matrix sigmoidal_deriv_function(Matrix mat);
Matrix tanh_deriv_function(Matrix mat);
Matrix relu_deriv_function(Matrix mat);
Matrix t_function(Matrix mat);

#endif