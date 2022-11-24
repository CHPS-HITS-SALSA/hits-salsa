#include <algorithm>
#include <boost/core/demangle.hpp>
#include <iostream>
#include <vector>

using std::cout, std::string, std::vector;

int index(const vector<string>& v, string k) {
    auto it = find(v.begin(), v.end(), k);
    int index = -1;
    if (it != v.end())
        index = it - v.begin();
    return index;
}

std::string demangle(auto x) {
    return boost::core::demangle(typeid(x).name());
}
