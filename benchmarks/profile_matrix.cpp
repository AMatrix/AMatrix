#include <iostream>
#include <cmath>
#include <string>

#include "timer.h"
#include "matrix.h"

template<class TMatrixType>
    void initialize(TMatrixType& TheMatrix) {
        for (std::size_t i = 0; i < TheMatrix.size1(); i++)
            for (std::size_t j = 0; j < TheMatrix.size2(); j++)
                TheMatrix(i, j) = j + 1.00;
    }

 template<class TMatrixType>
   void initializeInverse(TMatrixType& TheMatrix) {
        for (std::size_t i = 0; i < TheMatrix.size1(); i++)
            for (std::size_t j = 0; j < TheMatrix.size2(); j++)
                TheMatrix(i, j) = 1.00 / (i + 1);
    }

template<class TMatrixType, std::size_t TSize1, std::size_t TSize2>
    void Profile() {                     
        constexpr std::size_t repeat = 100000000;                                   
        TMatrixType A(TSize1, TSize2);                                   
        TMatrixType B(TSize1, TSize2);                                   
        TMatrixType C(TSize1, TSize2);                                   
        initialize(A);                                                   
        initialize(B);                                                   
        initialize(C);                                                   
        Timer timer;                                                     
        for (std::size_t i_repeat = 0; i_repeat < repeat; i_repeat++) { 
           C = A + B; 
           B = C;                                                    
        }                                                                
        auto elapsed = timer.elapsed().count();                          
        std::cout << "elapsed time : " << elapsed << std::endl;
        std::cout << C << std::endl;                                  
    }


int main() {
    Profile<AMatrix::Matrix<double, AMatrix::dynamic,AMatrix::dynamic>, 6, 6>();

    return 0;
}
