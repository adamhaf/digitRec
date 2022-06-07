//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H


#include "Dense.h"
#include "Digit.h"
#define MLP_SIZE 4


const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork{
private:
    Dense layer1;
    Dense layer2;
    Dense layer3;
    Dense layer4;
public:
    MlpNetwork(const Matrix weight[MLP_SIZE],const Matrix biases[MLP_SIZE]);
    Digit operator()(const Matrix& input);

};

#endif // MLPNETWORK_H
