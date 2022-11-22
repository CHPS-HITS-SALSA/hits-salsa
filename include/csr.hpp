#pragma once
#include <vector>

using size_t = std::size_t;

template <typename T>
class Csr {
    public:
        Csr(std::vector<T> const& sp_mtx);
        ~Csr() = default;

    private:
        std::vector<T> values;
        std::vector<size_t> col_idx;
        std::vector<size_t> row_idx;

        std::vector<T> getValues(){return values};
        std::vector<size_t> getCol(){return col_idx};
        std::vector<size_t> getRow(){return row_idx};

};
