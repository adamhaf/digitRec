//
// Created by adam on 04/09/2021.
//

#include <fstream>
#include "Matrix.h"
#define FAILED_ALLOC "I got a nulptr when trying to allocate memory (new)."
#define DIMS_NOT_GOOD "I got dims that are less or equal to zero"
#define MIN_SIZE 0.1
#define ERROR "Error:"
#define NUM_OF_FLOAT "I got less float then needed to put in the matrix"
#define MATRIX_SIZE "Matrix dims are not satisfied"

    /*
    * helps us calculate the index of the element as a 2d array
    */
    inline int index_calc(int rows,int cols,int row_size) {
        return (row_size) * rows + cols;
    }

    //is some cases we need to check where the matrix are equals so
    // I made a function that handle it
    void Matrix::is_equal(const Matrix &lhs) const {
        if (lhs.get_rows() != get_rows() || lhs.get_cols() != get_cols()) {
            std::cerr << ERROR << " " << MATRIX_SIZE << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    //constructors
    Matrix::Matrix() {
        //defaults constructors as demanded
        dims.rows = 1;
        dims.cols = 1;
        matrix_pointer = new (std::nothrow) float[num_of_val()];
        //here we will use one d array
        if(matrix_pointer == nullptr){
            std::cerr << FAILED_ALLOC << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    Matrix::Matrix(int rows,int cols) {
        if(rows <= 0 || cols <= 0){
            std::cerr << DIMS_NOT_GOOD << std::endl;
            exit(EXIT_FAILURE);
        }
        dims.rows = rows;
        dims.cols = cols;
        matrix_pointer = new (std::nothrow) float[num_of_val()];
        //here we will use one d array
        if(matrix_pointer == nullptr){
            std::cerr << FAILED_ALLOC << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    Matrix::Matrix(const Matrix &m) {
        dims.rows = m.get_rows();
        dims.cols = m.get_cols();
        matrix_pointer = new (std::nothrow) float[m.num_of_val()];
        //here we will use one d array
        if(matrix_pointer == nullptr){
            std::cerr << FAILED_ALLOC << std::endl;
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < m.num_of_val(); ++i) {
            matrix_pointer[i] = m.matrix_pointer[i];
        }
    }

    Matrix::~Matrix()noexcept{
        if(dims.rows == 0 && dims.cols == 0) return;
        delete[] matrix_pointer;
    }

    Matrix & Matrix::transpose() {
        Matrix copy(*this);
        for (int i = 0; i < get_rows(); ++i) {
            for (int j = 0; j < get_cols(); ++j) {
                matrix_pointer[index_calc(j, i, get_rows())] = \
                copy.matrix_pointer[index_calc(i, j, get_cols())];
            }
        }
        int temp = dims.rows;
        dims.rows = dims.cols;
        dims.cols = temp;
        return *this;
    }

    void Matrix::plain_print() const {
        for (int i = 0; i < get_rows(); ++i) {
            for (int j = 0; j < get_cols(); ++j) {
                int temp = index_calc(i, j, get_cols());
                std::cout << (this->matrix_pointer[temp]) << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix Matrix::vectorize() {
        //size i am working with 1d matrix, just need to change the dims
        dims.rows *= dims.cols;
        dims.cols = 1;
        return *this;
    }

    Matrix Matrix::dot(const Matrix &lhs) const {
        this->is_equal(lhs);
        Matrix dot(get_rows(), get_cols());
        for (int i = 0; i < num_of_val(); ++i) {
            dot.matrix_pointer[i] = matrix_pointer[i] * lhs.matrix_pointer[i];
        }
        return dot;
    }

    float Matrix::norm() const{
        double sum = 0;
        for (int i = 0; i < num_of_val(); ++i) {
            sum += matrix_pointer[i] * matrix_pointer[i];
        }
        return (float) sqrt(sum);
    }

    //operation:

    Matrix Matrix::operator+(const Matrix & lhs)const{
        this->is_equal(lhs);
        Matrix res(*this);
        for(int i=0;i<res.num_of_val(); ++i){
            res.matrix_pointer[i] += lhs.matrix_pointer[i];
        }
        return res;
    }

    Matrix& Matrix::operator=(const Matrix &lhs){
        if(&lhs == this){
            return *this;
        }
        this->~Matrix();
        dims.rows = lhs.get_rows();
        dims.cols = lhs.get_cols();
        matrix_pointer = new (std::nothrow) float[lhs.num_of_val()];
        //here we will use one d array
        if(matrix_pointer == nullptr){
            std::cerr << FAILED_ALLOC << std::endl;
            exit(EXIT_FAILURE);
        }
        for(int i=0;i<lhs.num_of_val();++i){
            matrix_pointer[i] = lhs.matrix_pointer[i];
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix& lhs)const{
        /*
         * just making the most annoying operation in all mathematics :-)
         */
        if ( get_cols() != lhs.get_rows()) {
            std::cerr << ERROR << " "<< MATRIX_SIZE << std::endl;
            exit(EXIT_FAILURE);
        }
        Matrix mul_res(get_rows(),lhs.get_cols());
        for(int i=0;i<get_rows();++i){
            for(int j=0;j< lhs.get_cols();++j){
                float temp=0;
                for(int k=0;k<get_cols();++k){
                    temp += matrix_pointer[index_calc(i,k,get_cols())]*\
                    lhs.matrix_pointer[index_calc(k,j,lhs.get_cols())];
                }
                int t = index_calc(i,j,mul_res.get_cols());
                mul_res.matrix_pointer[t]\
                = temp;
            }
        }
        return mul_res;
    }

    Matrix Matrix::operator*(const float x)const{
        for(int i=0;i<num_of_val();++i){
            matrix_pointer[i] *= x;
        }
        return *this;
    }

    Matrix& Matrix::operator+=(const Matrix &lhs){
        //first checking whether the dims are the same
        is_equal(lhs);
        //just adding value by value
        for(int i=0;i<lhs.num_of_val(); ++i){
                matrix_pointer[i] += lhs.matrix_pointer[i];
        }
        return *this;
    }

    float & Matrix::operator()(int i,int j){
        return matrix_pointer[index_calc(i,j,this->dims.cols)];
    }

    const float & Matrix::operator()(int i,int j)const{
        return matrix_pointer[index_calc(i,j,this->dims.cols)];
    }

    const float &Matrix::operator[](int i) const{
        return matrix_pointer[i];
    }

void read_binary_file(std::istream &file,Matrix& m){
    file.seekg(0, std::istream::end);
    int n_bytes = (int) file.tellg();
    file.seekg(0, std::istream::beg);
    unsigned int n = n_bytes/sizeof(float);
    if((int)n < m.num_of_val()){
        std::cerr << ERROR << " "<< NUM_OF_FLOAT << std::endl;
        exit(EXIT_FAILURE);
    }

    auto *temp = new (std::nothrow) float[n];
    //here we will use one d array
    if(temp == nullptr){
        std::cerr << FAILED_ALLOC << std::endl;
        exit(EXIT_FAILURE);
    }
    file.read(reinterpret_cast<char *>(temp),n_bytes);
    for(int i=0;i < m.get_cols()*m.get_rows(); ++i){
        m[i] = temp[i];
    }
    delete[] temp;
}


std::ostream& operator<<(std::ostream& s, const Matrix& m){
        for (int i = 0; i < m.get_rows(); ++i) {
            for (int j = 0; j < m.get_cols(); ++j) {
                int temp = index_calc(i, j, m.get_cols());
            if(m[temp] >= MIN_SIZE){
                s << "  ";
            } else
                s << "**";
        }
        s << std::endl;
    }
    return s;
}
