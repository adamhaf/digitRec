#include "Dense.h"

//
// Created by adam on 06/09/2021.
//
Dense::Dense(const Matrix &w,const Matrix &bias,ActivationType act_type):_w(w),
_bias(bias), _act_type(act_type){}

Activation Dense::get_activation() const{
    return Activation(this->_act_type);
}
Matrix Dense::operator()(const Matrix& input) const{
    /*
     * just doing matrix arithmetic as we defined in Matrix class
     * ,where for we don`t need to check the dims this is Matrix responsibility
     */
    Activation this_act = get_activation();
    return this_act( (_w*input) + _bias);
}
