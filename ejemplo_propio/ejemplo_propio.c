#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "h/matrix.h"
#include "h/neural_net.h"
#include "h/matrix_struct.h"
#include "h/neural_layer_struct.h"

static Matrix (*from_matrix_create_matrix) (int, int) = create_matrix;
static void (*from_matrix_fill_set_vector_matrix) (Matrix*, int, ...) = fill_set_vector_matrix;
static void (*from_matrix_free_matrix) (Matrix*) = free_matrix;
static void (*from_matrix_show_matrix) (Matrix) = show_matrix;

static void (*from_neural_net_create_neural_net) (NeuralLayer*, int*, int, Matrix, char) = create_neural_net;
static void (*from_neural_net_show_neural_net) (NeuralLayer*, int) = show_neural_net;
static void (*from_neural_net_free_neural_net) (NeuralLayer*, int*) = free_neural_net;
static void (*from_neural_net_train_neural_net) (NeuralLayer*, Matrix, int, float, int) = train_neural_net;
static void (*from_neural_net_show_final_output_neural_net) (NeuralLayer*, int) = show_final_output_neural_net;
static void (*from_neural_net_feed_forward_wi_neural_net) (NeuralLayer*, Matrix, int) = feed_forward_wi_neural_net;

int main(){
    srand(time(NULL));

    // UTILIZAR SIGMOIDAL
    
    int layers = 3;

    int *arq_nn = (int*) malloc(layers * sizeof(int));
    *(arq_nn + 0) = 4; // Layer 1 (input layer)
    *(arq_nn + 1) = 5; // Layer 2 (1 hidden layer)
    *(arq_nn + 2) = 4; // Layer 3 (output layer)

    Matrix input = from_matrix_create_matrix(16, *(arq_nn + 0));
    from_matrix_fill_set_vector_matrix(
        &input,
        input.r * input.c,
        0.0, 0.0, 0.0, 0.0,
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        1.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 0.0,
        1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        1.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        1.0, 0.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0
    );

    Matrix output = from_matrix_create_matrix(16, *(arq_nn + 2));
    from_matrix_fill_set_vector_matrix(
        &output,
        output.r * output.c,
        1.0, 1.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        1.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        0.0, 0.0, 0.0, 1.0,
        1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        1.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0
    );

    NeuralLayer *neural_net = (NeuralLayer*) malloc(layers * sizeof(NeuralLayer));
    from_neural_net_create_neural_net(neural_net, arq_nn, layers, input, 's');
    from_neural_net_show_neural_net(neural_net, layers);

    from_neural_net_train_neural_net(neural_net, output, layers, 0.03, 12000);

    printf("\n Neural Net after training\n");

    from_neural_net_show_neural_net(neural_net, layers);

    printf("\n Final Output\n");
    from_neural_net_show_final_output_neural_net(neural_net, layers);

    printf("\n Expected Output\n");
    from_matrix_show_matrix(output);

    /*printf("\n New Input = {0.5, 0.5, 0.5, 0.5}\n");
    Matrix n_input = from_matrix_create_matrix(1, *(arq_nn + 0));
    from_matrix_fill_set_vector_matrix(
        &n_input,
        n_input.c * n_input.r,
        0.5, 0.5, 0.5, 0.5
    );

    from_neural_net_feed_forward_wi_neural_net(neural_net, n_input, layers);

    printf("\n New output\n");
    from_neural_net_show_final_output_neural_net(neural_net, layers);*/

    from_neural_net_free_neural_net(neural_net, &layers);
    free((void*) arq_nn);
    free((void*) neural_net);
    from_matrix_free_matrix(&output);
}