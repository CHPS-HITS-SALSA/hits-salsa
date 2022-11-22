#include "csr.hpp"

template <typename T>
Csr<T>::Csr(std::vector<T> const& sp_mtx) {
    // sparsify the input matrix into CSR format
    int cmp = 0;
    int n = sqrt(sp_mtx.size());

    for(int i = 0; i < n; ++i){
        this->row_idx[i*n] = cmp;
        for(j = 0; i < n; ++j){
            if(sp_mtx[n*i+j] != 0){
                this->values[cmp] = sp_mtx[n*i+j];
                this->col_idx[cmp] = j;
                cmp++;
            }
        }
    }
    this->row_idx[n] = cmp;
}