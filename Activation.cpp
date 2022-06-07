//
// Created by adam on 06/09/2021.
//


#include "Activation.h"

Matrix Activation::relu_func(const Matrix &m){
    /*
     * here we will apply the Relu Function on the matrix, and we will
     * return a new function.
     */
    Matrix relu_m(m.get_rows(),m.get_cols());
    for(int i=0; i < m.get_rows()*m.get_cols();++i){
        float current_val = m[i];
        if(current_val < 0){
            relu_m[i] = 0;
        } else
            relu_m[i] = current_val;
    }
    return relu_m;
}

Matrix Activation::softmax_func(const Matrix &m) {
    /*
     * here we will make the matrix after applying soft max
     */
    Matrix softmax_m(m.get_rows(),m.get_cols());
    float sum =0;
    for(int i=0; i < m.get_rows()*m.get_cols();++i){
        float current_val = m[i];
        sum += std::exp(current_val);
        softmax_m[i] = std::exp(current_val);
    }
    return 1/sum*softmax_m;
}

Activation::Activation(ActivationType act_type): _act_type(act_type) {}

ActivationType Activation::get_activation_type()const {
    return _act_type;
}

Matrix Activation::operator()(const Matrix& m)const{
    //here we will send the right Matrix
    if(this->_act_type == RELU)
        return relu_func(m);
    return softmax_func(m);

}