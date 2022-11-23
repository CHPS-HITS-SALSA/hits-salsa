#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "utils.hpp"

using json = nlohmann::json;

int main() {
    vector<bool> adj = json_parse("datasets/100samples.json");

    // print_matrix(adj);
}
