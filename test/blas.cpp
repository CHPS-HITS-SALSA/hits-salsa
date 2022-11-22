#include "blas.hpp"
#include "csr.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

auto main(int32_t argc, char** argv) -> int32_t {
    std::vector<double> sp_mtx = {
        5.0, 0.0, 0.0, 0.0,
        0.0, 8.0, 0.0, 0.0,
        0.0, 0.0, 3.0, 0.0,
        0.0, 6.0, 0.0, 0.0
    };
    std::cout << "sp_mtx [" << std::endl;
    for (size_t i = 0; i < 4; ++i) {
        std::cout << "  [";
        for (size_t j = 0; j < 4; ++j) {
            std::cout << sp_mtx[i * 4 + j] << ", ";
        }
        std::cout << "\b\b]\n";
    }
    std::cout << "\b]" << std::endl;

    Csr<double> csr_mtx = Csr(sp_mtx);
    std::cout << "csr_mtx = " << csr_mtx << std::endl;

    const std::vector<double> x {1.0, 1.0, 1.0, 1.0};
    std::vector<double> y {0.0, 0.0, 0.0, 0.0};
    chps_blas::spmv(csr_mtx, x.data(), y.data());
    std::cout << "csr_mtx * unit_vec = y: [";
    for (auto val: y) {
        std::cout << val << ", ";
    }
    std::cout << "\b\b]" << std::endl;

    return 0;
}
