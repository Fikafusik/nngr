
#include "solver.hpp"

#include "orientation.hpp"
#include "problem.hpp"
#include "solution.hpp"

namespace nngr {

    solver_t::solver_t(problem_t problem)
    : m_horizontals{problem.horizontals.size()}
    , m_verticals{problem.verticals.size()}
    , m_problem{problem}
    , m_solution{problem}
    , m_islands{}
    , m_horizontals_ocean{problem}
    , m_verticals_ocean{problem}
    {
        init();
    }

    solution_t const& solver_t::solution() const {
        return m_solution;
    }

    void solver_t::init_islands(problem_t::value_type lines, orientation_t orientation) {
        for (size_t i = 0; i < lines.size(); ++i) {
            for (size_t j = 0; j < lines.size(); ++j) {
                
            }
        }
    }

    void solver_t::init_ocean() {

    }

    void solver_t::init() {
        init_islands(m_problem.horizontals, orientation_t::horizontal);
        init_islands(m_problem.verticals, orientation_t::vertical);

        init_ocean();
    }

    void solver_t::relax_oceans() {
        for (size_t i = 0; i < m_horizontals; ++i) {
            for (size_t j = 0; j < m_verticals; ++j) {
                // if one of the following is empty, then solution[i][j] = space
                if (m_horizontals_ocean[i][j].empty() || m_verticals_ocean[j][i].empty()) {
                    m_solution[i][j] = cell_t::space;

                    m_horizontals_ocean[i][j].clear();
                    m_verticals_ocean[j][i].clear();

                    // TODO: some islands may be splitted here, so they should be relaxed too
                }
            }
        }
    }

};