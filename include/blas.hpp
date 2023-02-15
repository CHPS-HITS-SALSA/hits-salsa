#pragma once

#include "csmat.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

namespace blas {
    /**
     * Computes the norm-2 of a vector.
     *
     * @param x An input vector.
     * @return The norm-2 of `x`.
     **/
    template <typename T>
    auto norm2(std::vector<T> const& x) -> T {
        return sqrt(std::reduce(x.begin(), x.end(), 0.0));
    }

    /**
     * Normalizes a vector.
     *
     * @param x An input vector.
     * @return The norm-2 of `x`.
     **/
    template <typename T>
    auto normalize(std::vector<T>& x) -> void {
        T norm = norm2(x);
        std::for_each(x.begin(), x.end(), [norm](T& v) {
            v /= norm;
        });
    }

    /**
     * Sparse matrix-vector multiplication for the Compressed Sparse format (CSR or CSC).
     *
     * @param mtx A matrix in the CS format.
     * @param x A vector.
     * @param y The output vector.
     **/
    template <typename T>
    auto spmv(CsMat<T>& mtx, T alpha, T const* x, T beta, T* y) -> void {
        size_t dim = mtx.get_outer_dim();

        std::vector<T> const& values = mtx.get_data();
        std::vector<size_t> const& indices = mtx.get_indices();
        std::vector<size_t> const& indptr = mtx.get_indptr();

        for (size_t i = 0; i < dim; ++i) {
            for (size_t j = indptr[i]; j < indptr[i + 1]; ++j) {
                y[i] += alpha * values[j] * x[indices[j]];
            }
            y[i] *= beta;
        }
    }
} // namespace blas
