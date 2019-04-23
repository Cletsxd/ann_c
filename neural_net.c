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
static Matrix (*from_math_functions_t_function) (Matrix) = t_function;
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

void create_neural_net(NeuralLayer *neural_net, int *arq_nn, int layers, Matrix input, char act_f){
    if(layers == 0){
        from_error_code_error_code(6);
        from_error_code_function_number(7);
        from_error_code_good_bye();
        exit(-1);
    }

    NeuralLayer *ap;

    ap = neural_net + 0;
    ap -> output = input;
    ap -> weights = from_matrix_create_null_matrix();
    ap -> bias = from_matrix_create_null_matrix();
    ap -> deltas = from_matrix_create_null_matrix();
    
    switch(act_f){
        case 's': ap -> function = NeuralLayer::Sigmoidal; break;
        case 't': ap -> function = NeuralLayer::Tanh; break;
        case 'r': ap -> function = NeuralLayer::Relu; break;
    }
    
    for(int i = 1; i < layers; i++){
        ap = neural_net + i;

        ap -> weights = from_matrix_create_matrix(*(arq_nn + (i - 1)), *(arq_nn + i));
        ap -> bias = from_matrix_create_matrix(1, *(arq_nn + i));
        ap -> output = from_matrix_create_null_matrix();
        ap -> deltas = from_matrix_create_null_matrix();
        ap -> function = NeuralLayer::Tanh;

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
        layer = neural_net + i;
        layer_p = neural_net + (i + 1);

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

void feed_forward_wi_neural_net(NeuralLayer *neural_net, Matrix input, int layers){
    NeuralLayer *layer;
    NeuralLayer *layer_p;

    Matrix res;

    for(int i = 0; i < layers - 1; i++){
        layer = neural_net + i;
        layer_p = neural_net + (i + 1);

        if(i == 0){
            res = from_math_functions_dot_function(input, layer_p -> weights);
        }else{
            res = from_math_functions_dot_function(layer -> output, layer_p -> weights);
        }

        res = from_math_functions_sum_wc_function(res, layer_p -> bias);

        switch(layer_p -> function){
            case NeuralLayer::Sigmoidal: res = from_math_functions_sigmoidal_act_function(res); break;
            case NeuralLayer::Tanh: res = from_math_functions_tanh_act_function(res); break;
            case NeuralLayer::Relu: res = from_math_functions_relu_act_function(res); break;
        }

        layer_p -> output = res;
    }
}

void backpropagation_neural_net(NeuralLayer *neural_net,  Matrix exp_output, int layers, float learning_rate){
    NeuralLayer *cur_layer;
    NeuralLayer *pre_layer;
    NeuralLayer *nex_layer;

    //- Para cada capa (de adelante hacia atrás):
    for(int layer = layers - 1; layer >= 1; layer--){
        cur_layer = neural_net + layer;
        pre_layer = neural_net + (layer - 1);

        //- Si es la última capa:
        if(layer == layers - 1){
            //- Calcular error (output layer - exp_output)
            Matrix error = from_math_functions_deriv_e2medio_function(cur_layer -> output, exp_output);

            //- Calcular deriv function (output layer)
            Matrix deriv;

            switch(cur_layer -> function){
                case NeuralLayer::Sigmoidal: deriv = from_math_functions_sigmoidal_deriv_function(cur_layer -> output); break;
                case NeuralLayer::Tanh: deriv = from_math_functions_tanh_deriv_function(cur_layer -> output); break;
                case NeuralLayer::Relu: deriv = from_math_functions_relu_deriv_function(cur_layer -> output); break;
            }

            //- Calcular delta layer (error * deriv)
            cur_layer -> deltas = from_math_functions_mult_matrix_function(error, deriv);
        }else{
            //- Si no es la última capa:

            nex_layer = neural_net + (layer + 1);

            //- Calcular transposición (weights layer + 1)
            Matrix w_t = from_math_functions_t_function(nex_layer -> weights);

            //- Calcular deriv (output layer)
            Matrix deriv;

            switch(cur_layer -> function){
                case NeuralLayer::Sigmoidal: deriv = from_math_functions_sigmoidal_deriv_function(cur_layer -> output); break;
                case NeuralLayer::Tanh: deriv = from_math_functions_tanh_deriv_function(cur_layer -> output); break;
                case NeuralLayer::Relu: deriv = from_math_functions_relu_deriv_function(cur_layer -> output); break;
            }

            //- Calcular dot (delta layer +1, transposición)
            Matrix m_dot = from_math_functions_dot_function(nex_layer -> deltas, w_t);


            //- Calcular delta layer (multiplicación normal de matrices (dot, deriv))
            cur_layer -> deltas = from_math_functions_mult_matrix_function(m_dot, deriv);
        }
        // Descenso del Gradiente

        // Actualización de Bias
        //- Calcular mean (deltas layer)
        Matrix mean = from_math_functions_mean_matrix_function(cur_layer -> deltas);

        //- Calcular mult_float (mean * learning rate)
        Matrix mult_float = from_math_functions_mult_matrix_float_function(mean, learning_rate);

        //- Calcular resta (bias layer, mult_float)
        cur_layer -> bias = from_math_functions_subs_matrix_function(cur_layer -> bias, mult_float);
        //- Actualizar Bias = resta

        // Actualización de Weights
        //- Calcular transposición (output layer - 1)
        Matrix o_t = from_math_functions_t_function(pre_layer -> output);

        //- Calcular dot (transposición, delta layer)
        Matrix dot = from_math_functions_dot_function(o_t, cur_layer -> deltas);

        //- Calcular mult_float (dot, learning_rate)
        mult_float = from_math_functions_mult_matrix_float_function(dot, learning_rate);

        //- Calcular resta (weights layer, mult_float)
        cur_layer -> weights = from_math_functions_subs_matrix_function(cur_layer -> weights, mult_float);
        //- Actualizar Weights = resta
    }
}

void show_final_output_neural_net(NeuralLayer *neural_net, int layers){
    NeuralLayer *layer;

    layer = neural_net + (layers - 1);

    from_matrix_show_matrix(layer -> output);
}

void train_neural_net(NeuralLayer *neural_net, Matrix exp_output, int layers, float learning_rate, int epochs){
    for(int i = 0; i < epochs; i++){
        feed_forward_neural_net(neural_net, layers);
        backpropagation_neural_net(neural_net, exp_output, layers, learning_rate);
    }
}
/*
int main(){
    srand(time(NULL));

    int layers = 3;

    int *arq_nn = (int*) malloc(layers * sizeof(int));
    *(arq_nn + 0) = 2; // Layer 1 (input layer) = 2 neurons
    *(arq_nn + 1) = 3; // Layer 2 (1 hidden layer) = 3 neurons
    *(arq_nn + 2) = 1; // Layer 3 (output layer) = 1 neuron

    Matrix input = from_matrix_create_matrix(4, *(arq_nn + 0));
    from_matrix_fill_set_vector_matrix(
        &input,
        input.c * input.r,
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0
    );

    Matrix output = from_matrix_create_matrix(4, *(arq_nn + 2));
    from_matrix_fill_set_vector_matrix(
        &output,
        output.c * output.r,
        0.0,
        1.0,
        1.0,
        0.0
    );

    NeuralLayer *neural_net = (NeuralLayer*) malloc(layers * sizeof(NeuralLayer));
    create_neural_net(neural_net, arq_nn, layers, input);
    show_neural_net(neural_net, layers);

    feed_forward_neural_net(neural_net, layers);

    printf("\n Final Output\n");
    show_final_output_neural_net(neural_net, layers);

    backpropagation_neural_net(neural_net, output, layers, 0.01);

    train_neural_net(neural_net, output, layers, 0.15, 10000);

    printf("\n Neural Net after training\n");

    show_neural_net(neural_net, layers);

    printf("\n Final Output\n");
    show_final_output_neural_net(neural_net, layers);

    free_neural_net(neural_net, &layers);
    free((void*) arq_nn);
    free((void*) neural_net);
    from_matrix_free_matrix(&output);
}
*/