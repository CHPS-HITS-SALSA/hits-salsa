#pragma once

#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

template <typename T>
using DenseMatrix = std::vector<T>;

/**
 * Kind of the compressed storage format.
 *
 * The non-zero values of a sparse matrix are stored as the row and column location of the non-zero
 * values, with a compression along the rows (`Csr`) or columns (`Csc`) indices.
 **/
enum class CsKind {
    Csr,
    Csc,
};

/**
 * Compressed storage matrix, either in CSR or CSC format.
 *
 * The `CsMat` class is generic over the scalar type `T` of the underlying elements of the matrix.
 * The data is owned by the `CsMat` class.
 * The non-zero locations and values are stored in vectors of size `nnz`.
 *
 * The index pointer vector `indptr` of size corresponding to the number of columns/rows
 * (depending on storage) stores the cumulative sum of non-zero elements for each column/row.
 * The number of non-zero elements of the i-th column/row can be computed as:
 *     `indptr[i + 1] - indptr[i]`.
 * The total number of non-zero elements is thus `nnz = indptr[get_outer_dim() + 1]`.
 *
 * This index pointer array can then be used to efficiently index the indices and data vectors,
 * which respectively contain the column/row indices and the values of the non-zero elements.
 **/
template <typename T>
class CsMat {
public:
    ~CsMat() = default;

    static auto new_csr(size_t ncols, size_t nrows, DenseMatrix<T> const& mtx) -> CsMat {
        std::vector<T> data;
        std::vector<size_t> indices;
        std::vector<size_t> indptr(nrows + 1, 0);

        for (size_t i = 0; i < nrows; ++i) {
            for (size_t j = 0; j < ncols; ++j) {
                if (mtx[i * ncols + j] != 0.0) {
                    indices.push_back(j);
                    data.push_back(mtx[i * ncols + j]);
                }
            }
            indptr[i + 1] = indices.size();
        }

        return CsMat(CsKind::Csr, ncols, nrows, data, indices, indptr);
    }

    static auto new_csc(size_t ncols, size_t nrows, DenseMatrix<T> const& mtx) -> CsMat {
        std::vector<T> data;
        std::vector<size_t> indices;
        std::vector<size_t> indptr(ncols + 1, 0);

        for (size_t j = 0; j < ncols; ++j) {
            for (size_t i = 0; i < nrows; ++i) {
                if (mtx[i * ncols + j] != 0.0) {
                    indices.push_back(i);
                    data.push_back(mtx[i * ncols + j]);
                }
            }
            indptr[j + 1] = indices.size();
        }

        return CsMat(CsKind::Csc, ncols, nrows, data, indices, indptr);
    }

    [[nodiscard]] auto transposed() const -> CsMat<T> {
        auto transposed_indptr = std::vector<size_t>(get_inner_dim() + 1, 0);
        auto transposed_indices = std::vector<size_t>(get_nnz());
        auto transposed_data = std::vector<T>(get_nnz());

        auto const& outer_indptr = get_indptr();
        auto const& outer_indices = get_indices();
        auto const& outer_data = get_data();

        for (size_t i = 0; i < get_nnz(); ++i) {
            ++transposed_indptr[outer_indices[i] + 1];
        }
        for (size_t i = 0; i < get_inner_dim(); ++i) {
            transposed_indptr[i + 1] += transposed_indptr[i];
        }
        for (size_t i = 0; i < get_outer_dim(); ++i) {
            for (size_t j = outer_indptr[i]; j < outer_indptr[i + 1]; ++j) {
                auto col = outer_indices[j];
                auto dest = transposed_indptr[col];
                transposed_indices[dest] = i;
                transposed_data[dest] = outer_data[j];
                ++transposed_indptr[col];
            }
        }
        for (int i = get_inner_dim() - 1; i > 0; --i) {
            transposed_indptr[i] = transposed_indptr[i - 1];
        }
        transposed_indptr[0] = 0;

        return CsMat<T>(
            this->storage == CsKind::Csr ? CsKind::Csc : CsKind::Csr,
            this->nrows,
            this->ncols,
            transposed_data,
            transposed_indices,
            transposed_indptr
        );
    }

    [[nodiscard]] inline auto get_storage() const -> CsKind {
        return this->storage;
    };

    [[nodiscard]] inline auto get_ncols() const -> size_t {
        return this->ncols;
    };

    [[nodiscard]] inline auto get_nrows() const -> size_t {
        return this->nrows;
    };

    [[nodiscard]] inline auto get_nnz() const -> size_t {
        return this->data.size();
    }

    [[nodiscard]] inline auto get_outer_dim() const -> size_t {
        return this->storage == CsKind::Csr ? this->nrows : this->ncols;
    }

    [[nodiscard]] inline auto get_inner_dim() const -> size_t {
        return this->storage == CsKind::Csc ? this->nrows : this->ncols;
    }

    [[nodiscard]] inline auto get_data() const -> std::vector<T> const& {
        return this->data;
    };

    [[nodiscard]] inline auto get_indices() const -> std::vector<size_t> const& {
        return this->indices;
    };

    [[nodiscard]] inline auto get_indptr() const -> std::vector<size_t> const& {
        return this->indptr;
    };

    [[nodiscard]] inline auto get_mut_data() -> std::vector<T>& {
        return this->data;
    };

    [[nodiscard]] inline auto get_mut_indices() -> std::vector<size_t>& {
        return this->indices;
    };

    [[nodiscard]] inline auto get_mut_indptr() -> std::vector<size_t>& {
        return this->indptr;
    };

    auto inline operator==(CsMat const& rhs) const -> bool {
        bool is_eq = true;
        for (const auto& [self_v, rhs_v]: std::make_pair(this->data, rhs->data)) {
            if (self_v != rhs_v) {
                is_eq = false;
            }
        }

        for (const auto& [self_v, rhs_v]: std::make_pair(this->indices, rhs->indices)) {
            if (self_v != rhs_v) {
                is_eq = false;
            }
        }

        for (const auto& [self_v, rhs_v]: std::make_pair(this->indptr, rhs->indptr)) {
            if (self_v != rhs_v) {
                is_eq = false;
            }
        }

        return is_eq;
    }

    friend auto operator<<(std::ostream& stream, CsMat const& mat) -> std::ostream& {
        stream << "CsMat { storage: " << mat.get_storage_as_str();
        stream << ", ncols: " << mat.ncols << ", nrows: " << mat.nrows;
        stream << ", data: [";
        for (auto val : mat.data) {
            stream << val << ", ";
        }
        stream << "\b\b], indices: [";
        for (auto val : mat.indices) {
            stream << val << ", ";
        }
        stream << "\b\b], indptrs: [";
        for (auto val : mat.indptr) {
            stream << val << ", ";
        }
        stream << "\b\b] }";
        return stream;
    }

private:
    CsKind storage;
    size_t ncols;
    size_t nrows;
    std::vector<T> data;
    std::vector<size_t> indices;
    std::vector<size_t> indptr;

    CsMat() : storage(CsKind::Csr), ncols(0), nrows(0) {}
    CsMat(
        CsKind storage,
        size_t ncols,
        size_t nrows,
        std::vector<T> const& data,
        std::vector<size_t> const& indices,
        std::vector<size_t> const& indptr
    ) : storage(storage),
        ncols(ncols),
        nrows(nrows),
        data(data),
        indices(indices),
        indptr(indptr)
    {}

    [[nodiscard]] inline auto get_storage_as_str() const -> std::string {
        switch (this->storage) {
            case CsKind::Csr:
                return "CSR";
            case CsKind::Csc:
                return "CSC";
            default:
                return "unknown";
        }
    };
};