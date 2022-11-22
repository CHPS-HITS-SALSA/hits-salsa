#pragma once

#include <cmath>
#include <iostream>
#include <vector>

using size_t = std::size_t;

template <typename T>
class Csr {
  public:
    Csr(std::vector<T> const& sp_mtx)
        : nb_rows(static_cast<size_t>(sqrt(sp_mtx.size())))
    {
        size_t nnz = 0;
        this->row_idx.push_back(nnz);
        for (size_t i = 0; i < this->nb_rows; ++i) {
            for (size_t j = 0; j < this->nb_rows; ++j) {
                if (sp_mtx[i * this->nb_rows + j] != 0.0) {
                    this->values.push_back(sp_mtx[i * this->nb_rows + j]);
                    this->col_idx.push_back(j);
                    nnz++;
                }
            }
            this->row_idx.push_back(nnz);
        }
    }
    ~Csr() = default;

    friend std::ostream& operator<<(std::ostream& os, Csr const& csr) {
        os << "Csr { values: [";
        for (auto val: csr.get_values()) {
            os << val << ", ";
        }
        os << "\b\b], col_idx: [";
        for (auto val: csr.get_col_idx()) {
            os << val << ", ";
        }
        os << "\b\b], row_idx: [";
        for (auto val: csr.get_row_idx()) {
            os << val << ", ";
        }
        os << "\b\b], nb_rows: " << csr.get_nb_rows() << " }";
        return os;
    }

    std::vector<T> const& get_values() const { return values; };
    std::vector<size_t> const& get_col_idx() const { return col_idx; };
    std::vector<size_t> const& get_row_idx() const { return row_idx; };
    size_t get_nb_rows() const { return nb_rows; };

    std::vector<T>& get_values() { return values; };
    std::vector<size_t>& get_col_idx() { return col_idx; };
    std::vector<size_t>& get_row_idx() { return row_idx; };

  private:
    std::vector<T> values;
    std::vector<size_t> col_idx;
    std::vector<size_t> row_idx;
    size_t nb_rows;
};
