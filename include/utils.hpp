#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

using std::cout, std::vector, std::string;

int index(const vector<string> v, const string k);

template <typename T>
void print_matrix(const vector<T> mat) {
    size_t dim = sqrt(mat.size());

    for (size_t i = 0; i < dim; ++i) {
        cout << "  [";
        for (size_t j = 0; j < dim; ++j) {
            cout << mat[i * dim + j] << ", ";
        }
        cout << "\b\b]\n";
    }
}

template <typename T>
vector<T> adjacency_matrix_parse(const string file) {
    std::ifstream f(file);
    json jdata = json::parse(f);
    vector<string> ids{};

    for (auto it : jdata) {
        if (it.find("asin") != it.end()) {
            if (!count(ids.begin(), ids.end(), it["asin"]))
                ids.push_back(it["asin"]);
            if ((it.contains("related") && it["related"].contains("also_viewed"))) {
                vector<string> v2 = it["related"]["also_viewed"];
                ids.insert(ids.end(), v2.begin(), v2.end());
            }
        }
    }

    cout << "Unique identifiers : " << ids.size() << '\n';

    const size_t size = ids.size() * ids.size();
    // std::array<bool, size> adj = { 0 };
    vector<T> adj(size, 0);

    cout << "Adjacent matrix size :" << adj.size() << std::endl;

    for (auto it : jdata) {
        string id = it["asin"];
        vector<string> viewed{};
        if ((it.contains("related") && it["related"].contains("also_viewed")))
            viewed = (vector<string>)it["related"]["also_viewed"];

        for (string v : viewed) {
            adj[index(ids, id) * ids.size() + index(ids, v)] = 1;
            adj[index(ids, v) * ids.size() + index(ids, id)] = 1;
        }
    }
    return adj;
}