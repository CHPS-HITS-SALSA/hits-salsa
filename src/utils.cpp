#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

int index(vector<string> v, string k) {
    auto it = find(v.begin(), v.end(), k);
    int index = -1;
    if (it != v.end())
        index = it - v.begin();
    return index;
}

void print_matrix(bool** mat) {
    // size_t size = sizeof(mat) / sizeof(mat[0]);
    // cout << "size : " << size << endl;
    // // size_t size = mat.size();
    // for (int i = 0; i < size; ++i) {
    //     for (int j = 0; j < size; ++j) {
    //         cout << mat[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
}

bool** json_parse(string file) {
    ifstream f(file);
    json jdata = json::parse(f);
    vector<string> ids;

    // cout << jdata.dump(2) << endl;

    // for (auto it = jdata.begin(); it != jdata.end(); ++it) {
    int i = 0;
    for (auto it : jdata) {
        if (it.find("asin") != it.end()) {
            if (!count(ids.begin(), ids.end(), it["asin"]))
                ids.push_back(it["asin"]);
            if ((it.contains("related") && it["related"].contains("also_viewed"))) {
                auto v2 = it["related"]["also_viewed"];
                ids.insert(ids.end(), v2.begin(), v2.end());
                // cout << it["related"]["also_viewed"] << endl;
                cout << i << endl;
            }
        }
        i++;
    }

    cout << "Unique identifiers : " << ids.size() << endl;

    // bool adj[ids.size()][ids.size()] = {};
    // vector<vector<bool>>;

    bool** adj = 0;
    adj = new bool*[ids.size()];
    for (size_t i = 0; i < ids.size(); ++i) {
        adj[i] = new bool[ids.size()];
        for (size_t j = 0; j < ids.size(); ++j) {
            adj[i][j] = 0;
        }
    }

    for (auto it : jdata) {
        string id = it["asin"];
        vector<string> viewed;
        if ((it.contains("related") && it["related"].contains("also_viewed")))
            viewed = (vector<string>)it["related"]["also_viewed"];

        for (string v : viewed) {
            adj[index(ids, id)][index(ids, v)] = 1;
            adj[index(ids, v)][index(ids, id)] = 1;
        }
    }
    print_matrix(adj);

    return adj;
}