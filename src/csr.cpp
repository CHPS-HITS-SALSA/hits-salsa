#include "csr.hpp"

template <typename T>
Csr<T>::Csr(std::vector<T> const& sp_mtx) {
    size_t nnz = 0;
    this->row_idx.push_back(nnz);
    for (size_t i = 0; i < this->nb_rows; ++i) {
        for (size_t j = 0; i < this->nb_rows; ++j) {
            if (sp_mtx[i * this->nb_rows + j] != 0.0) {
                this->values.push_back(sp_mtx[i * this->nb_rows + j]);
                this->col_idx.push_back(j);
                nnz++;
            }
        }
        this->row_idx.push_back(nnz);
    }
}