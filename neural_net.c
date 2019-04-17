#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix_struct.h"
#include "matrix.h"
#include "neural_layer_struct.h"
#include "error_code.h"
#include "neural_net.h"
#include "math_functions.h"

static Matrix (*from_matrix_create_matrix) (int, int) = create_matrix;
static Matrix (*from_matrix_create_null_matrix) (void) = create_null_matrix;
static void (*from_matrix_fill_matrix) (Matrix*) = fill_matrix;
static void (*from_matrix_show_matrix) (Matrix) = show_matrix;
static void (*from_matrix_free_matrix) (Matrix*) = free_matrix;
static void (*from_matrix_fill_set_vector_matrix) (Matrix*, int, ...) = fill_set_vector_matrix;
static bool (*from_matrix_is_null_matrix) (Matrix*) = is_null_matrix;

static Matrix (*from_math_functions_dot_function) (Matrix, Matrix) = dot_function;
static Matrix (*from_math_functions_sum_wc_function) (Matrix, Matrix) = sum_wc_function;
static Matrix (*from_math_functions_subs_matrix_function) (Matrix, Matrix) = subs_matrix_function;
static Matrix (*from_math_functions_deriv_e2medio_function) (Matrix, Matrix) = deriv_e2medio_function;
static Matrix (*from_math_functions_mult_matrix_function) (Matrix, Matrix) = mult_matrix_function;
static Matrix (*from_math_functions_mean_matrix_function) (Matrix) = mean_matrix_function;
static Matrix (*from_math_functions_mult_matrix_float_function) (Matrix, float) = mult_matrix_float_function;
static Matrix (*from_math_functions_sigmoidal_act_function) (Matrix) = sigmoidal_act_function;
static Matrix (*from_math_functions_tanh_act_function) (Matrix) = tanh_act_function;
static Matrix (*from_math_functions_relu_act_function) (Matrix) = relu_act_function;
static Matrix (*from_math_functions_sigmoidal_deriv_function) (Matrix) = sigmoidal_deriv_function;
static Matrix (*from_math_functions_tanh_deriv_function) (Matrix) = tanh_deriv_function;
static Matrix (*from_math_functions_relu_deriv_function) (Matrix) = relu_deriv_function;

static void (*from_error_code_error_code) (int) = error_code;
static void (*from_error_code_function_number) (int) = function_number;
static void (*from_error_code_good_bye) (void) = good_bye;

struct NeuralLayer;

void create_neural_net(NeuralLayer *neural_net, int *arq_nn, int layers, Matrix input){
    if(layers == 0){
        from_error_code_error_code(6);
        from_error_code_function_number(7);
        from_error_code_good_bye();
        exit(-1);
    }

    NeuralLayer *ap;

    ap = (neural_net + 0);
    ap -> output = input;
    ap -> weights = from_matrix_create_null_matrix();
    ap -> bias = from_matrix_create_null_matrix();
    ap -> deltas = from_matrix_create_null_matrix();
    ap -> function = NeuralLayer::Sigmoidal;

    for(int i = 1; i < layers; i++){
        ap = (neural_net + i);

        ap -> weights = from_matrix_create_matrix(*(arq_nn + (i - 1)), *(arq_nn + i));
        ap -> bias = from_matrix_create_matrix(1, *(arq_nn + i));
        ap -> output = from_matrix_create_null_matrix();
        ap -> deltas = from_matrix_create_null_matrix();
        ap -> function = NeuralLayer::Sigmoidal;

        from_matrix_fill_matrix(&ap -> weights);
        from_matrix_fill_matrix(&ap -> bias);
    }
}

void show_neural_net(NeuralLayer *neural_net, int layers){
    if(layers == 0){
        from_error_code_error_code(7);
        from_error_code_function_number(8);
        from_error_code_good_bye();
        exit(-1);
    }

    printf("\n > Layer 1 (input layer): \n");
    from_matrix_show_matrix(neural_net -> output);

    NeuralLayer *ap;
    ap = neural_net + 0;

    for(int i = 1; i < layers; i++){
        ap = neural_net + i;
        printf("\n > Layer %i: \n", i + 1);
        printf(" - Weights\n");
        from_matrix_show_matrix(ap -> weights);
        printf(" - Bias\n");
        from_matrix_show_matrix(ap -> bias);
        
        /*switch(ap -> function){
            case NeuralLayer::Sigmoidal: printf("Sigmoidal\n");
            break;

            case NeuralLayer::Tanh: printf("Tanh\n");
            break;
        }*/
    }
}

// Elimina la red
void free_neural_net(NeuralLayer *neural_net, int *layers){
    if(*layers == 0){
        from_error_code_error_code(7);
        from_error_code_function_number(9);
        from_error_code_good_bye();
        exit(-1);
    }

    NeuralLayer *ap;

    for(int i = 0; i < *layers; i++){
        ap = neural_net + i;
        if(!from_matrix_is_null_matrix(&ap -> weights)){
            from_matrix_free_matrix(&ap -> weights);
        }

        if(!from_matrix_is_null_matrix(&ap -> bias)){
            from_matrix_free_matrix(&ap -> bias);
        }

        if(!from_matrix_is_null_matrix(&ap -> deltas)){
            from_matrix_free_matrix(&ap -> deltas);
        }

        if(!from_matrix_is_null_matrix(&ap -> output)){
            from_matrix_free_matrix(&ap -> output);
        }
    }

    *layers = 0;
}

void feed_forward_neural_net(NeuralLayer *neural_net, int layers){
    NeuralLayer *layer;
    NeuralLayer *layer_p;

    Matrix res;

    for(int i = 0; i < layers - 1; i++){
        /*printf(" DOT {output layer %i & weights layer %i}\n", i, i + 1);
        printf(" SUMA_WC {DOT & bias layer %i}\n", i + 1);
        printf(" ACTIVE_F {SUMA_WC}\n");
        printf(" SEET_OUTPUT {layer %i}\n", i + 1);
        printf("\n\n");*/

        layer = neural_net + i;
        layer_p = neural_net + i + 1;

        res = from_math_functions_dot_function(layer -> output, layer_p -> weights);
        res = from_math_functions_sum_wc_function(res, layer_p -> bias);

        switch(layer_p -> function){
            case NeuralLayer::Sigmoidal: res = from_math_functions_sigmoidal_act_function(res); break;
            case NeuralLayer::Tanh: res = from_math_functions_tanh_act_function(res); break;
            case NeuralLayer::Relu: res = from_math_functions_relu_act_function(res); break;
        }

        layer_p -> output = res;
    }
}

void show_final_output_neural_net(NeuralLayer *neural_net, int layers){
    NeuralLayer *layer;

    layer = neural_net + (layers - 1);

    from_matrix_show_matrix(layer -> output);
}

int main(){
    srand(time(NULL));

    int layers = 3;

    int *arq_nn = (int*) malloc(layers * sizeof(int));
    *(arq_nn + 0) = 2; // Layer 1 (input layer) = 2 neurons
    *(arq_nn + 1) = 3; // Layer 2 (1 hidden layer) = 3 neurons
    *(arq_nn + 2) = 1; // Layer 3 (output layer) = 1 neuron

    Matrix input = create_matrix(4, *(arq_nn + 0));
    from_matrix_fill_set_vector_matrix(
        &input,
        input.c * input.r,
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0
    );

    NeuralLayer *neural_net = (NeuralLayer*) malloc(layers * sizeof(NeuralLayer));
    create_neural_net(neural_net, arq_nn, layers, input);
    show_neural_net(neural_net, layers);

    feed_forward_neural_net(neural_net, layers);

    printf("\n Final Output\n");
    show_final_output_neural_net(neural_net, layers);

    free_neural_net(neural_net, &layers);
    free((void*) arq_nn);
    free((void*) neural_net);
}