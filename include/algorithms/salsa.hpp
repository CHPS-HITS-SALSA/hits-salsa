#pragma once

#include "blas.hpp"
#include "csmat.hpp"

#include <utility>
#include <vector>

/// This function implements the Stochastic Approach for Link-Structure Analysis (SALSA) algorithm.
/// It computes two scoring vectors: authority and hub. These represent the authoriy and hub scores
/// for each node of the sparse matrix used as input.
///
/// @param mtx The input sparse matrix.
/// @param error The epsilon threshold used to determine when the algorithm has converged.
/// @return A tuple containing the authority and hub scoring vectors.
template <typename T>
auto salsa(CsMat<T> const& A, double error) -> std::pair<std::vector<T>, std::vector<T>> {
    // TODO: A_r <- for each A row r: r / |r|
    // CsMat<T> A_r = ...;

    // TODO: A_c <- for each A col c: c / |c|
    // CsMat<T> A_c = ...;

    // TODO: A_cT <- A_c'
    // CsMat<T> A_cT = A_c.transpose();

    // TODO: A_tilde <- A_c' * A_r.
    // CsMat<T> A_tilde = blas::spmm(A_cT, A_r);

    // TODO: H_tilde <- A_r * A_c'.
    // CsMat<T> H_tilde = blas::spmm(A_r, A_cT);

    // TODO: Compute the dominant eigenvectors for each tilde matrix.
    // std::vector<T> a = blas::dominant_eigenvector(A_tilde);
    // std::vector<T> h = blas::dominant_eigenvector(H_tilde);

    // return std::make_pair(a, h);
}