#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "neural_net.h"
#include "matrix_struct.h"
#include "neural_layer_struct.h"

static Matrix (*from_matrix_create_matrix) (int, int) = create_matrix;
static void (*from_matrix_fill_set_vector_matrix) (Matrix*, int, ...) = fill_set_vector_matrix;
static void (*from_matrix_free_matrix) (Matrix*) = free_matrix;

static void (*from_neural_net_create_neural_net) (NeuralLayer*, int*, int, Matrix) = create_neural_net;
static void (*from_neural_net_show_neural_net) (NeuralLayer*, int) = show_neural_net;
static void (*from_neural_net_free_neural_net) (NeuralLayer*, int*) = free_neural_net;
static void (*from_neural_net_train_neural_net) (NeuralLayer*, Matrix, int, float, int) = train_neural_net;
static void (*from_neural_net_show_final_output_neural_net) (NeuralLayer*, int) = show_final_output_neural_net;

int main(){
    srand(time(NULL));

    int layers = 2;

    int *arq_nn = (int*) malloc(layers * sizeof(int));
    *(arq_nn + 0) = 3; // Layer 1 (input layer) = 2 neurons
    *(arq_nn + 1) = 1; // Layer 2 (1 hidden layer) = 3 neurons

    // Las entradas:
        // Ej1 | Ej2 | Ej3 | Ej4
        //  0  |  1  |  1  |  0
        //  0  |  1  |  0  |  1
        //  1  |  1  |  1  |  1
    
    Matrix input = from_matrix_create_matrix(4, *(arq_nn + 0));
    from_matrix_fill_set_vector_matrix(
        &input,
        input.c * input.r,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 0.0, 1.0,
        0.0, 1.0, 1.0
    );

    Matrix output = from_matrix_create_matrix(4, *(arq_nn + 1));
    from_matrix_fill_set_vector_matrix(
        &output,
        input.r * input.c,
        0.0,
        1.0,
        1.0,
        0.0
    );

    NeuralLayer *neural_net = (NeuralLayer*) malloc(layers * sizeof(NeuralLayer));
    from_neural_net_create_neural_net(neural_net, arq_nn, layers, input);
    from_neural_net_show_neural_net(neural_net, layers);

    from_neural_net_train_neural_net(neural_net, output, layers, 0.1, 5000);

    printf("\n Neural Net after training\n");

    from_neural_net_show_neural_net(neural_net, layers);

    printf("\n Final Output\n");
    from_neural_net_show_final_output_neural_net(neural_net, layers);

    from_neural_net_free_neural_net(neural_net, &layers);
    free((void*) arq_nn);
    free((void*) neural_net);
    from_matrix_free_matrix(&output);
}