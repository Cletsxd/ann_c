struct NeuralLayer{
    Matrix weights;
    Matrix bias;
    Matrix deltas;
    Matrix output;
    
    enum ActivationFunctions{
        Sigmoidal,
        Tanh,
        Relu,
    };

    ActivationFunctions function;
};