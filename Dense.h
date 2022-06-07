#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Matrix.h"
#include "Activation.h"

class Dense{
    private:
        Matrix _w;
        Matrix _bias;
        ActivationType _act_type;
    public:
    /*
    * here will make the layers needed for recognize the number
    */
    Dense(const Matrix & w,const Matrix & bias,ActivationType act_type);

    //getters
    inline const Matrix & get_weights()const{
        return _w;
    };
    inline const Matrix & get_bias ()const{
        return _bias;
    };
    Activation get_activation() const;

    //operator
    /*
     * we will make simple function that will make the operation
     */
    Matrix operator()(const Matrix& input) const;
};

#endif //C___PROJECT_DENSE_H
