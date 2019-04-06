#ifndef _NEURAL_NET_H_
#define _NEURAL_NET_H_

struct NeuralLayer;

void create_neural_net(NeuralLayer *neural_net, int *arq_nn, int layers, Matrix input);
void show_neural_net(NeuralLayer *neural_net, int layers);
void free_neural_net(NeuralLayer *neural_net, int *layers);

#endif