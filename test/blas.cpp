#include "blas.hpp"

#include "csmat.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

auto main(int32_t argc, char** argv) -> int32_t {
    size_t ncols = 3;
    size_t nrows = 4;
    const std::vector<double> unit_vec(nrows, 1.0);
    std::vector<double> res_csr(nrows, 0.0);
    std::vector<double> res_csc(nrows, 0.0);

    // Example sparse matrix
    std::vector<double> sp_mtx = {
        0.0, 0.0, 8.0, 5.0, 0.0, 0.0, 0.0, 3.0, 0.0, 6.0, 0.0, 0.0,
    };
    std::cout << "sp_mtx = [" << std::endl;
    for (size_t i = 0; i < nrows; ++i) {
        std::cout << "  [";
        for (size_t j = 0; j < ncols; ++j) {
            std::cout << sp_mtx[i * ncols + j] << ", ";
        }
        std::cout << "\b\b]\n";
    }
    std::cout << "]" << std::endl;

    // Sparsify the sparse matrix to a CSR format
    CsMat<double> csr_mtx = CsMat<double>::new_csr(ncols, nrows, sp_mtx);
    std::cout << "csr_mtx = " << csr_mtx << std::endl;
    // Sparsify the sparse matrix to a CSC format
    CsMat<double> csc_mtx = CsMat<double>::new_csc(ncols, nrows, sp_mtx);
    std::cout << "csc_mtx = " << csc_mtx << std::endl;

    // Compute matrix-vector product using CSR format
    blas::spmv(csr_mtx, 1.0, unit_vec.data(), 1.0, res_csr.data());
    std::cout << "csr_mtx * unit_vec = [";
    for (double& val : res_csr) {
        std::cout << val << ", ";
    }
    std::cout << "\b\b]" << std::endl;
    // Compute matrix-vector product using CSC format
    blas::spmv(csc_mtx, 1.0, unit_vec.data(), 1.0, res_csc.data());
    std::cout << "csc_mtx * unit_vec = [";
    for (double& val : res_csc) {
        std::cout << val << ", ";
    }
    std::cout << "\b\b]" << std::endl;

    // Norm-2 of `res_csr`
    std::cout << "\n|res_csr| = " << blas::norm2(res_csr) << std::endl;
    // normalize `res`
    blas::normalize(res_csr);
    std::cout << "res_csr / |res_csr| = [";
    for (double& val : res_csr) {
        std::cout << val << ", ";
    }
    std::cout << "\b\b]" << std::endl;

    // Norm-2 of `res_csc`
    std::cout << "\n|res_csc| = " << blas::norm2(res_csc) << std::endl;
    // normalize `res`
    blas::normalize(res_csc);
    std::cout << "res_csc / |res_csc| = [";
    for (double& val : res_csc) {
        std::cout << val << ", ";
    }
    std::cout << "\b\b]" << std::endl;

    return 0;
}
