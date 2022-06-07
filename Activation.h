//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

class Activation{
    private:
        static Matrix relu_func(const Matrix &m);
        static Matrix softmax_func(const Matrix &m);
        ActivationType _act_type;
    public:
        explicit Activation(ActivationType act_type);
        ActivationType get_activation_type() const;
        Matrix operator()(const Matrix& m) const;
};

#endif //ACTIVATION_H
