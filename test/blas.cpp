#include "blas.hpp"
#include "csr.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

constexpr size_t dim = 4;

auto main(int32_t argc, char** argv) -> int32_t {
    const std::vector<double> unit_vec {1.0, 1.0, 1.0, 1.0};
    std::vector<double> res {0.0, 0.0, 0.0, 0.0};

    // Example sparse matrix
    std::vector<double> sp_mtx = {
        5.0, 0.0, 0.0, 0.0,
        0.0, 8.0, 0.0, 0.0,
        0.0, 0.0, 3.0, 0.0,
        0.0, 6.0, 0.0, 0.0
    };
    std::cout << "sp_mtx = [" << std::endl;
    for (size_t i = 0; i < dim; ++i) {
        std::cout << "  [";
        for (size_t j = 0; j < dim; ++j) {
            std::cout << sp_mtx[i * dim + j] << ", ";
        }
        std::cout << "\b\b]\n";
    }
    std::cout << "]" << std::endl;

    // Sparisify the sparse matrix to a CSR format
    Csr<double> csr_mtx = Csr(sp_mtx);
    std::cout << "csr_mtx = " << csr_mtx << std::endl;

    // Compute matrix-vector product using CSR format
    chps_blas::spmv(csr_mtx, unit_vec.data(), res.data());
    std::cout << "csr_mtx * unit_vec = [";
    for (auto val: res) {
        std::cout << val << ", ";
    }
    std::cout << "\b\b]" << std::endl;

    return 0;
}
