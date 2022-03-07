#pragma once

#include <vector>
#include <string>

#include "cell.hpp"
#include "problem.hpp"

namespace nngr {

    class solution_t {
    public:
        solution_t(size_t horizontals, size_t verticals);
        solution_t(problem_t problem);

        std::string to_string() const;

        std::vector<cell_t> const& operator[](size_t horizontal) const;
        std::vector<cell_t>& operator[](size_t horizontal);

    private:
        std::vector<std::vector<cell_t>> m_cells;
    };

    std::ostream& operator<<(std::ostream& os, const solution_t& solution);

}; // namespace nngr