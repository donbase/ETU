#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <QString>
#include <iomanip>
#include <cmath>
#include "addon.h"
using namespace std;

enum EPrintMode
{
    //EPrintModeClassic,
    EPrintModeRank,
    //EPrintModeCanonic,
};


template <class number>
class Matrix
{
    EPrintMode printMode;
    int size1;
protected:
    int size2;
public:
    number** M;
    Matrix(int, int, number*);
    Matrix();
    number** Trans();
    number  Det();
    int rang_mat();
    void Show();
    template <class T>
    friend std::ostream& operator<< (std::ostream&, Matrix<T>&);


    void setPrintMode(EPrintMode);
    template <class T>
    friend QString& operator<< (QString&, Matrix<T>&);



};

template <class number>
Matrix<number>::Matrix(int size_r, int size_c, number* values){
    // Выделение памяти под матрицу размером n*n и заполнение ее нулями
    size1 = size_r;
    size2 = size_c;
    int k = 0;
    //int size = size1*size2;
    M = (number**)malloc(size1*sizeof(number*));
    for(int i = 0; i < size1; ++i)
        M[i] = (number*)malloc(size2*sizeof(number));

    for(int i = 0; i < size1; ++i){
        for(int j = 0; j < size2; ++j){
            M[i][j] = values[k];
            k++;
        }
    }
}

template <class number>
Matrix<number>::Matrix(){
    // Выделение памяти под матрицу размером n*n и заполнение ее нулями
    //size1 = size_r;
    //size2 = size_c;
    //int k = 0;
    //int size = size1*size2;
    //M = (number**)malloc(size1*sizeof(number*));
    //for(int i = 0; i < size1; ++i)
      //  M[i] = (number*)malloc(size2*sizeof(number));

    //for(int i = 0; i < size1; ++i){
      //  for(int j = 0; j < size2; ++j){
        //    M[i][j] = values[k];
         //   k++;
        //}
    //}
}


/*Matrix::Matrix(){
    // Выделение памяти под матрицу размером 3*3 и заполнение ее нулями

    size1 = 3;
    size2 = 3;
    M = (number**)malloc(size1*sizeof(number*));
    for(int i = 0; i < size1; ++i)
        M[i] = (number*)malloc(size2*sizeof(number));

    for(int i = 0; i < size1; ++i){
        for(int j = 0; j < size2; ++j){
            M[i][j] = 0;
        }
    }
}*/

/*std::ostream& operator<< (std::ostream& os, Matrix& m){
    int p = 2;
    for(int i = 0; i < m.size1; ++i){
        p = 0;
        for(int j = 0; j < m.size2; ++j){
            std::cout<<setiosflags(std::ios::left);
            os<<std::setw(p)<<m.M[j][i]<<' ';
            p +=1;
        }
        os<<'\n';
    }
    return os;
}
*/


template <class number>
number** Matrix<number>::Trans(){
    number t;
    number** new_M = (number**)malloc(size2*sizeof(number*));
    for(int i = 0; i < size2; ++i)
        new_M[i] = (number*)malloc(size1*sizeof(number));


    //int k = 0;
    for(int i = 0; i < size1; ++i)
    {
        for(int j = 0; j < size2; ++j)
        {
            t = M[i][j];
            new_M[j][i] = t;
        }
    }

    return new_M;
    //for(int i = 0; i < size1; i++)
    //  delete M[i];
    //delete M;
    //M = new_M;
    //swap(size2, size1);
}


template <class number>
number Matrix<number>::Det(){
    //if (size1 != size2) return 0;
    number M_copy[size1][size2];
    int size = size1;
    // Копирование матрицы
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            M_copy[i][j] = M[i][j];

    number tmp;
    for(int k = 0; k < size - 1; ++k){
        for(int i = k + 1; i < size; ++i){
            tmp = M_copy[i][k] / M_copy[k][k];
            for(int j = 0; j < size; ++j){
                M_copy[i][j] = M_copy[i][j] - M_copy[k][j]*tmp;
            }
        }
    }

    number det = M_copy[0][0];
    for(int i = 1; i < size; ++i){
        det = det*M_copy[i][i];
    }
    return det;
}




template <class number>
int Matrix<number>::rang_mat()
{
    number M_copy[size1][size2];

    // Копирование матрицы
    for (int i = 0; i < size1; i++)
        for (int j = 0; j < size2; j++)
            M_copy[i][j] = M[i][j];

    int r = 0;
    int q = 1;

    while(q<=min(size1,size2))
    {
        number **B = new number*[q];
        for(int w=0;w<q;w++) B[w] = new number[q];

        for(int a=0;a<(size1-(q-1));a++)
        {
            for(int b=0;b<(size2-(q-1));b++)
            {
                for(int c=0;c<q;c++)
                {
                    for(int d=0;d<q;d++)
                    {
                        B[c][d] = M_copy[a+c][b+d];

                    }
                }
                if(!(det_mat(B,q)==0))
                {
                    r = q;
                }
            }
        }
        q++;

        delete[] B;
    }
    return r;

}

#endif // MATRIX_H
