#include <stdio.h>
#include "error_code.h"

void error_code(int e){
    switch(e){
        case 1:
            printf("\n> ERROR 1: Can't create Matrix with those dimensions.");
        break;

        case 2:
            printf("\n> ERROR 2: Can't fill Matrix because the argument `matrix` is not created or NULL.");
        break;

        case 3:
            printf("\n> ERROR 3: Can't show Matrix because the argument `matrix` is not created or NULL.");
        break;

        case 4:
            printf("\n> ERROR 4: Matrix has created but not filled.");
        break;

        case 5:
            printf("\n> ERROR 5: Matrix is already NULL.");
        break;

        case 6:
            printf("\n> ERROR 6: Can't create neural net because the arg `layers` is 0.");
        break;

        case 7:
            printf("\n> ERROR 7: Neural net has no layers.");
        break;

        case 8:
            printf("\n> ERROR 8: The operation can't resolve. The arguments are incorrect.");
        break;

        case 9:
            printf("\n> ERROR 9: The operation can't resolve. The `b` Matrix has a value of rows > 1.");
        break;

        case 10:
            printf("\n> ERROR 10: The operation can't resolve. The columns of Matrix `a` and `b` are not equal.");
        break;

        case 11:
            printf("\n> ERROR 11: The operation can't resolve. The rows of Matrix `a` and `b` are not equal.");
        break;

        case 12:
            printf("\n> ERROR 12: The operation can't resolve. The Matrix is NULL or not filled.");
        break;
    }
}

void function_number(int f){
    switch(f){
        case 1:
            printf(" Function: create_matrix().\n");
        break;

        case 2:
            printf(" Function: test_fill_matrix().\n");
        break;

        case 3:
            printf(" Function: fill_matrix().\n");
        break;

        case 4:
            printf(" Function: show_matrix().\n");
        break;

        case 5:
            printf(" Function: free_matrix().\n");
        break;

        case 6:
            printf(" Function: fill_set_vector_matrix().\n");
        break;

        case 7:
            printf(" Function: create_neural_net().\n");
        break;

        case 8:
            printf(" Function: show_neural_net().\n");
        break;

        case 9:
            printf(" Function: free_neural_net().\n");
        break;

        case 10:
            printf(" Function: fill_zeros_matrix().\n");
        break;

        case 11:
            printf(" Function: dot_function().\n");
        break;

        case 12:
            printf(" Function: suma_wc_function().\n");
        break;

        case 13:
            printf(" Function: subs_matrix_function().\n");
        break;

        case 14:
            printf(" Function: deriv_e2medio_function().\n");
        break;

        case 15:
            printf(" Function: mult_matrix_function().\n");
        break;

        case 16:
            printf(" Function: mean_matrix_function().\n");
        break;

        case 17:
            printf(" Function: mult_matrix_float_function().\n");
        break;
    }
}

void good_bye(){
    printf("\n> THE PROGRAM HAS FINISHED\n");
}