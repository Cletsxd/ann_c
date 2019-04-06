#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix_struct.h"
#include "matrix.h"
#include "neural_layer_struct.h"

static Matrix (*from_matrix_create_matrix) (int, int) = create_matrix;
static void (*from_matrix_fill_matrix) (Matrix*) = fill_matrix;
static void (*from_matrix_show_matrix) (Matrix) = show_matrix;
static void (*from_matrix_free_matrix) (Matrix*) = free_matrix;
static void (*from_matrix_fill_set_vector_matrix) (Matrix*, int, ...) = fill_set_vector_matrix;

struct NeuralLayer;

void set_null_neural_net(NeuralLayer *neural_net, int layers){
    NeuralLayer *ap;

    for(int i = 0; i < layers; i++){
        ap = neural_net + i;
        ap -> weights = NULL;
    }
}

void create_neural_net(NeuralLayer *neural_net, int *arq_nn, int layers, Matrix input){
    NeuralLayer *ap;

    ap = (neural_net + 0);
    ap -> output = input;

    for(int i = 1; i < layers; i++){
        ap = (neural_net + i);

        ap -> weights = from_matrix_create_matrix(*(arq_nn + (i - 1)), *(arq_nn + i));
        ap -> bias = from_matrix_create_matrix(1, *(arq_nn + i));

        from_matrix_fill_matrix(&ap -> weights);
        from_matrix_fill_matrix(&ap -> bias);

        //from_matrix_show_matrix(ap -> weights);
        //from_matrix_show_matrix(ap -> bias);

        /*from_matrix_free_matrix(&ap -> weights);
        from_matrix_free_matrix(&ap -> bias);*/
    }
}

void show_neural_net(NeuralLayer *neural_net, int layers){
    printf("\n > Layer 1 (input layer): \n");
    from_matrix_show_matrix(neural_net -> output);

    NeuralLayer *ap;
    ap = neural_net + 0;

    for(int i = 1; i < layers; i++){
        ap = neural_net + i;
        printf("\n > Layer %i: \n", i);
        printf(" - Weights\n");
        from_matrix_show_matrix(ap -> weights);
        printf(" - Bias\n");
        from_matrix_show_matrix(ap -> bias);
    }
}

void free_neural_net(NeuralLayer *neural_net, int layers){
    NeuralLayer *ap;

    for(int i = 0; i < layers; i++){
        ap = neural_net + i;
        if(ap -> weights != NULL){
            from_matrix_free_matrix(ap -> weights);
        }

        if(ap -> bias != NULL){
            from_matrix_free_matrix(ap -> bias);
        }

        if(ap -> deltas != NULL){
            from_matrix_free_matrix(ap -> deltas);
        }

        if(ap -> output != NULL){
            from_matrix_free_matrix(ap -> output);
        }
    }
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

    free((void*) arq_nn);
    from_matrix_free_matrix(&input);
    free((void*) neural_net);
}