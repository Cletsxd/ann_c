#include <stdio.h>
#include "error_code.h"

void error_code(int e){
    switch(e){
        case 1:
            printf("\n> ERROR 1: Can't create matrix with those dimensions.");
        break;

        case 2:
            printf("\n> ERROR 2: Can't fill matrix because the argument `matrix` is not created or NULL.");
        break;

        case 3:
            printf("\n> ERROR 3: Can't show matrix because the argument `matrix` is not created or NULL.");
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
    }
}

void good_bye(){
    printf("\n> THE PROGRAM HAS FINISHED\n");
}