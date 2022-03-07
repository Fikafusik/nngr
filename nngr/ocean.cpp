
#include "ocean.hpp"

#include <cstddef>
#include <vector>

#include "island.hpp"
#include "problem.hpp"

namespace nngr {

    ocean_t::ocean_t(size_t horizontals, size_t verticals)
    : m_horizontals{horizontals}
    , m_verticals{verticals}
    , m_ocean{ m_horizontals, { m_verticals, std::vector<size_t>{} } }
    {
    }

    ocean_t::ocean_t(problem_t problem)
    : ocean_t{problem.horizontals.size(), problem.verticals.size()}
    {
    }

    ocean_t::value_type const& ocean_t::operator[](size_t index) const {
        return m_ocean[index];
    }

    ocean_t::value_type& ocean_t::operator[](size_t index) {
        return m_ocean[index];
    }

    size_t const& ocean_t::horizontals() const {
        return m_horizontals;
    }

    size_t const& ocean_t::verticals() const {
        return m_verticals;
    }

    void ocean_t::add(island_t island) {
        
    }
};