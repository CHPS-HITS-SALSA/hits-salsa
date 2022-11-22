#pragma once
#include <vector>

using size_t = std::size_t;

template <typename T>
class Csr {
  public:
    Csr(std::vector<T> const& sp_mtx);
    ~Csr() = default;

    std::vector<T> const& get_values() const {
        return values;
    };
    std::vector<size_t> const& get_col_idx() const {
        return col_idx;
    };
    std::vector<size_t> const& get_row_idx() const {
        return row_idx;
    };
    size_t get_nb_rows() const {
        return nb_rows;
    };

    std::vector<T>& get_values() {
        return values;
    };
    std::vector<size_t>& get_col_idx() {
        return col_idx;
    };
    std::vector<size_t>& get_row_idx() {
        return row_idx;
    };

  private:
    std::vector<T> values;
    std::vector<size_t> col_idx;
    std::vector<size_t> row_idx;
    size_t nb_rows;
};
