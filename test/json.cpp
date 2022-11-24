#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    std::vector<bool> adj = adjacency_matrix_parse<bool>("datasets/100samples.json");

    // print_matrix(adj);
}
