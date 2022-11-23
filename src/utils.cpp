#include <boost/core/demangle.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using std::cout, std::string, std::vector;

string demangle(auto x) {
    return boost::core::demangle(typeid(x).name());
}

int index(vector<string> v, string k) {
    auto it = find(v.begin(), v.end(), k);
    int index = -1;
    if (it != v.end())
        index = it - v.begin();
    return index;
}

// template <typename T>
void print_matrix(vector<bool> mat) {
    size_t dim = sqrt(mat.size());

    for (size_t i = 0; i < dim; ++i) {
        cout << "  [";
        for (size_t j = 0; j < dim; ++j) {
            cout << mat[i * dim + j] << ", ";
        }
        cout << "\b\b]\n";
    }
}

vector<bool> json_parse(string file) {
    std::ifstream f(file);
    json jdata = json::parse(f);
    vector<string> ids;

    // cout << jdata.dump(2) << '\n';

    // for (auto it = jdata.begin(); it != jdata.end(); ++it) {
    for (auto it : jdata) {
        if (it.find("asin") != it.end()) {
            if (!count(ids.begin(), ids.end(), it["asin"]))
                ids.push_back(it["asin"]);
            if ((it.contains("related") && it["related"].contains("also_viewed"))) {
                auto v2 = it["related"]["also_viewed"];
                ids.insert(ids.end(), v2.begin(), v2.end());
            }
        }
    }

    cout << "Unique identifiers : " << ids.size() << '\n';

    const size_t size = ids.size() * ids.size();
    // std::array<bool, size> adj = { 0 };
    vector<bool> adj(size, 0);

    cout << "Adjacent matrix size :" << adj.size() << std::endl;

    for (auto it : jdata) {
        string id = it["asin"];
        vector<string> viewed;
        if ((it.contains("related") && it["related"].contains("also_viewed")))
            viewed = (vector<string>)it["related"]["also_viewed"];

        for (string v : viewed) {
            adj[index(ids, id) * ids.size() + index(ids, v)] = 1;
            adj[index(ids, v) * ids.size() + index(ids, id)] = 1;
        }
    }
    return adj;
}