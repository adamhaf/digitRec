//
// Created by adam on 06/09/2021.
//

#define NOT_OK_WEIGHT "The Weight That I Got Doesn't fit to any right dims"
#define NOT_OK_BIASES "The Biases That I Got Doesn't fit to any right dims"
#include "MlpNetwork.h"
#define WEIGHTS_DIMS_SIZE 4

void weight_biases_checker(const Matrix weight[MLP_SIZE],\
    const Matrix biases[MLP_SIZE]){
    //checking that we got the correct dims,
    //here we assume that the weight and biases have the same amount of correct
    //dims
    bool weight_is_ok = false;
    bool biases_is_ok = false;
    for(int i =0; i <MLP_SIZE;++i){
        for(int j=0; j <WEIGHTS_DIMS_SIZE;++j){
            if(weight[i].get_rows() == weights_dims[j].rows &&
                    weight[i].get_cols() == weights_dims[j].cols)
                weight_is_ok = true;
            if(biases[i].get_rows() == bias_dims[j].rows &&
               biases[i].get_cols() == bias_dims[j].cols)
                biases_is_ok = true;
        }
    }

    if(!weight_is_ok){
        std::cerr << NOT_OK_WEIGHT << std::endl;
        exit(EXIT_FAILURE);
    }
    if(!biases_is_ok){
        std::cerr << NOT_OK_BIASES << std::endl;
        exit(EXIT_FAILURE);
    }
}

MlpNetwork::MlpNetwork(const Matrix weight[MLP_SIZE],const Matrix \
biases[MLP_SIZE]):
        layer1(Dense(weight[0], biases[0], RELU)),
        layer2(Dense(weight[1], biases[1], RELU)),
        layer3(Dense(weight[2], biases[2], RELU)),
        layer4(Dense(weight[3], biases[3], SOFTMAX))
{
    weight_biases_checker(weight,biases);
    //just making each layer
}
Digit MlpNetwork::operator()(const Matrix& input) {
    //moving though the layer and getting the output
    Matrix x1 = layer1(input);
    Matrix x2 = layer2(x1);
    Matrix x3 = layer3(x2);
    Matrix output = layer4(x3);
    //finding the maxed value
    float max=0;
    unsigned int num=0;
    for(unsigned int i =0; i <(unsigned int) output.get_cols() * \
    output.get_rows();++i){
        if(output[(int)i] > max){
            max = output[(int)i];
            num = i;
        }
    }
    return Digit{num,max};
}
