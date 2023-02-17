#include "algorithms/hits.hpp"

#include "csmat.hpp"

#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

auto main() -> int32_t {
    CsMat<double> csr = CsMat<double>::csr_parse("datasets/500k.csr");

    std::cout << "file read" << std::endl;

    auto result = algorithms::hits(csr, 0.1);
    std::vector<double> hub_scores = result.first;
    std::vector<double> authority_scores = result.second;

    std::cout << "\n\033[32mTest passed!\033[0m\n";

    return EXIT_SUCCESS;
}
