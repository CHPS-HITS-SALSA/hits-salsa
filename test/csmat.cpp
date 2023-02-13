#include "csmat.hpp"

#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

auto main() -> int32_t {
    std::vector<double> dense_mtx = {
        1.0, 0.0, 4.0, 0.0,
        0.0, 2.0, 0.0, 5.0,
        0.0, 0.0, 3.0, 6.0,
    };

    std::cout << "CSR matrix:\n  ";
    CsMat<double> csr_mtx = CsMat<double>::new_csr(4, 3, dense_mtx);
    std::cout << csr_mtx << "\n";

    std::cout << "CSC matrix:\n  ";
    CsMat<double> csc_mtx = CsMat<double>::new_csc(4, 3, dense_mtx);
    std::cout << csc_mtx << "\n";

    std::cout << "\nTransposed CSR matrix (equals CSC):\n  ";
    CsMat<double> transposed_csr_mtx = csr_mtx.transposed();
    std::cout << transposed_csr_mtx << "\n";

    std::cout << "Transposed CSC matrix (equals CSR):\n  ";
    CsMat<double> transposed_csc_mtx = csc_mtx.transposed();
    std::cout << transposed_csc_mtx << "\n";

    assert(csc_mtx == transposed_csr_mtx);
    assert(csr_mtx == transposed_csc_mtx);
    std::cout << "\n\033[32mTest passed!\033[0m\n";

    return EXIT_SUCCESS;
}
