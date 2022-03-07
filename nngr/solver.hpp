#pragma once

#include "island.hpp"
#include "ocean.hpp"
#include "problem.hpp"
#include "solution.hpp"

namespace nngr {

    class solver_t {
    public:
        solver_t(problem_t problem);

        solution_t const& solution() const;

        void init_islands(problem_t::value_type lines, orientation_t orientation);
        void init_ocean();
        void init();

        void relax_oceans();

    private:
        
        size_t m_horizontals;
        size_t m_verticals;
        problem_t m_problem;
        solution_t m_solution;
        std::vector<island_t> m_islands;
        ocean_t m_horizontals_ocean;
        ocean_t m_verticals_ocean;
    };

};