// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <cassert>
#include <iostream>
#include <ostream>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;
class Matrix{
    private:
        matrix_dims dims = {0, 0};
        float *matrix_pointer;
        /*
         * just for avoiding write each time row*col
         */
        inline int num_of_val() const{
            return get_cols() * get_rows();
        }
        /*
         * in some function we net to make sure that the matrix that we got is
         * equal in there dims.
         */

        void is_equal(const Matrix &lhs) const;
    public:
        //construes
        Matrix();
        /*
         * the simple contractures just getting a 2 ints and making matrix
         */
        Matrix(int rows, int cols);
        /*
         * copy contracture
         */
        Matrix(const Matrix &m);
        /*
         * simple destructor for deleting the dynamic array
         */
        ~Matrix() noexcept;

        inline int get_rows() const{
            return dims.rows;
        }

        inline int get_cols() const{
            return dims.cols;
        }

        Matrix & transpose();
        /*
        * by using the overloading operation << we will print easily;
        */
        void plain_print() const;

        Matrix vectorize();
        /*
         * jute multiplying as demanded
         */
        Matrix dot(const Matrix &lhs) const;

        float norm() const;
        /*
         * we need to return matrix for enabling x+y+z etc
         */
        Matrix operator+(const Matrix & lhs) const;
        /*
         * here we will return just ref for avoiding copy the all matrix
         */
        Matrix& operator=(const Matrix & lhs);
        /*
         * just a simple matrix multiplication function
         */
        Matrix operator*(const Matrix & lhs) const;

        Matrix operator*(float x) const;

        Matrix& operator+=(const Matrix &lhs);
        /*
         * by getting i and j we will be able to send the value of this
         */
        float &operator()(int i,int j);

        const float &operator()(int i,int j) const;

        inline float &operator[](int i){
            return matrix_pointer[i];
        }

        const float &operator[](int i) const;

        friend std::ostream& operator<<(std::ostream& s, const Matrix& h);

        friend void read_binary_file(std::istream & file,Matrix& m);

        inline friend Matrix operator*(float x,Matrix m){
            return m*x;
        }
};
#endif //MATRIX_H
