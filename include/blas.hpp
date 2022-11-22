#pragma once

#include "csr.hpp"

namespace chps_blas {
    /**
     * Sparse matrix-vector multiplication for the CSR format.
     **/
    template <typename T>
    void spmv(Csr<T>& mtx, T const* x, T* y) {
        for (size_t i = 0; i < mtx.get_nb_rows(); ++i) {
            for (size_t j = mtx.get_row_idx()[i]; j < mtx.get_row_idx()[i + 1] - 1; ++j) {
                y[i] += mtx.get_values()[j] * x[mtx.get_col_idx()[j]];
            }
        }
    }
} // namespace chps_blas
