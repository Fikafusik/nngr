
#include "solution.hpp"

namespace nngr {

    solution_t::solution_t(size_t horizontals, size_t verticals)
    : m_cells{ horizontals, { verticals, cell_t::undefined } } {
    }

    solution_t::solution_t(problem_t problem)
    : solution_t{ problem.horizontals.size(), problem.verticals.size() } {
    }

    std::string solution_t::to_string() const {
        std::string result{};

        for (auto const& horizontals : m_cells) {
            for (auto const& cell : horizontals) {
                result += static_cast<char>(cell);
            }
            result += '\n';
        }

        return result;
    }

    std::vector<cell_t> const& solution_t::operator[](size_t horizontal) const {
        return m_cells[horizontal];
    }

    std::vector<cell_t>& solution_t::operator[](size_t horizontal) {
        return m_cells[horizontal];
    }

    std::ostream& operator<<(std::ostream& os, const solution_t& solution)
    {
        os << solution.to_string();
        return os;
    }

}; // namespace nngr